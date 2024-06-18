#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>
#include "Networker.h"
#include <thread>
#include <boost/algorithm/string/split.hpp>
#include "Protocol.h"
#include <boost/algorithm/string/classification.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),dbWorker(std::make_shared<DataBaseWorker>()),
    net(std::make_shared<Networker>( 1337, 1200,std::string("127.0.0.1"))),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbWorker->start_db();
    connect(ui->page_4,&RedactingCarState::sendCarStateSignal,this,&MainWindow::receiveCarState);
    std::vector<std::string> sql = {"*"};
    auto cars = dbWorker->getData(sql);
    ui->page_3->setRows(cars);
    connect(net.get(),&Networker::dataRecieves,this,&MainWindow::setTableData);
    run();
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::shared_ptr<DataBaseWorker> MainWindow::getDb()
{
    return dbWorker;
}


void MainWindow::receiveCarState(std::vector<std::string> carState)
{
    auto result = dbWorker->add_mes(carState);
    if(result != "OK")
    {
        QMessageBox::warning(this,"Ошибка",result.c_str());
        return;
    }
    ui->page_3->setRow(carState);
}

void MainWindow::setTableData(std::string data)
{
    std::vector<std::string> vectorData;
    CarStateMes cars;
    boost::split(vectorData,data,boost::is_any_of(" "));
    auto val = std::stoi(vectorData.at(0));
    switch(val)
    {
    case e_MessageType::e_GetFullData:
    {
        std::vector<std::string> sql = {"*"};
        auto cars = dbWorker->getData(sql);
        std::thread thread([cars](std::shared_ptr<Networker> net)
        {
        for( auto &car : cars)
        {
        CarStateMes mes_to_send;
        mes_to_send.fromString(car);
        auto string = mes_to_send.toString();
        net->sendMessage(std::move(string));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        },net);
       thread.detach();

    } break;
    case e_MessageType::e_MessageType_commnication:
    {
    std::cout<<"Message \n";
    cars.fromString(vectorData);
    std::string sql = " INSERT INTO " + dbWorker->getTableName() + " ( id, name ) VALUES (";
    sql+= vectorData.at(1);
    sql+= ", '";
    sql+= cars.name;
    sql+= "');";
    auto result = dbWorker->add_mes(vectorData);
    std::cout<<result;
    break;
     if(result != "OK")
    {
        QMessageBox::warning(this,"Ошибка",result.c_str());
        return;
    }
    ui->page_3->setRow(vectorData);
    } break;
    default:
    {

    }
    }
}

void MainWindow::run()
{
}
