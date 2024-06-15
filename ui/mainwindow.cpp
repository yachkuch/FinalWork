#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>
#include "Networker.h"
#include <thread>
#include <boost/algorithm/string/split.hpp>
MainWindow::MainWindow(boost::asio::io_context &context,QWidget *parent) :
    QMainWindow(parent),context(context),dbWorker(std::make_shared<DataBaseWorker>()),net(std::make_shared<Networker>(context, 1337, std::string("127.0.0.1"))),
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
