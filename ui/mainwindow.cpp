#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>
#include "Networker.h"
#include <thread>
#include <boost/algorithm/string/split.hpp>
#include "Protocol.h"
#include <boost/algorithm/string/classification.hpp>

MainWindow::MainWindow(boost::asio::io_context &context,QWidget *parent) :
    QMainWindow(parent),context(context),dbWorker(std::make_shared<DataBaseWorker>()),
    net(std::make_shared<Networker>(context, 1337, std::string("127.0.0.1"))),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbWorker->start_db();
    connect(ui->page_4,&RedactingCarState::sendCarStateSignal,this,&MainWindow::receiveCarState);
    std::vector<std::string> sql = {"*"};
    auto cars = dbWorker->getData(sql);
    ui->page_3->setRows(cars);
    net->start_server();
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
        for( auto &car : cars)
        {
        CarStateMes mes_to_send;
        mes_to_send.fromString(car);
        net->sendMessage(mes_to_send.toString());
        }
    } break;
    case e_MessageType::e_MessageType_commnication:
    {
    cars.fromString(vectorData);
    auto result = dbWorker->add_mes(vectorData);
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
auto ping = [](boost::asio::io_context &context)
{
    while(true)
    {
    context.poll();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};
    std::thread a(ping, std::ref(context));
    a.detach();
}
