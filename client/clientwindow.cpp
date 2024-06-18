#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <thread>

#include "Networker.h"
#include "Protocol.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <QPushButton>
#include <QAction>
#include <QTime>
#include <QSpinBox>

ClientWindow::ClientWindow(QWidget *parent) : QMainWindow(parent),networker(std::make_shared<Networker>(1200,1337, std::string("127.0.0.1"))),
                                                                                ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    connect(networker.get(), &Networker::dataRecieves, this, &ClientWindow::setTableData);
    model = new QStandardItemModel(0, 7);
    model->setHeaderData(0, Qt::Horizontal, "Номер");
    model->setHeaderData(1, Qt::Horizontal, "Марка");
    model->setHeaderData(2, Qt::Horizontal, "Пробег");
    model->setHeaderData(3, Qt::Horizontal, "Топливо");
    model->setHeaderData(4, Qt::Horizontal, "Состояние");
    model->setHeaderData(5, Qt::Horizontal, "Имя арендатора");
    model->setHeaderData(6, Qt::Horizontal, "Время аренды");

    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setVisible(false);

    connect(ui->update,&QPushButton::pressed,this,&ClientWindow::senRequest);
    connect(ui->pushButton,&QPushButton::pressed,this,&ClientWindow::sendGettingCarMessage);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::addButtom(std::string namer)
{
    //ui->cars_but->addAction(new QAction(namer.data(), ui->cars_but));
}

void ClientWindow::setTableData(std::string data)
{
    std::vector<std::string> vectorData;
    CarStateMes cars;
    boost::split(vectorData, data, boost::is_any_of(" "));

    int index = -1;
    try
    {
        index = std::stoi(vectorData.at(1));
    }
    catch (const std::exception &e)
    {
        return;
    }
    auto row_number = model->rowCount();
    auto iter = row_to_index.find(index);
    if (iter == row_to_index.end())
    {
        addButtom(vectorData.at(1));
        row_to_index[index] = row_number;
        for (int i = -1; const auto &el : vectorData)
        {
            if (i > model->columnCount())
                return;
            model->setItem(row_number, i, new QStandardItem(QString(el.data())));
            i++;
        }
        return;
    }
    for (int i = -1; const auto &el : vectorData)
    {
        if (i > model->columnCount())
            return;
        auto item = model->item(iter->second, i);
        item->setData(QVariant(el.data()));
        i++;
    }
}

void ClientWindow::sendGettingCarMessage()
{
    auto text = ui->spinBox->value();
    auto iter = row_to_index.find(text);
    if (iter == row_to_index.end()) return;
    CarStateMes cars;
    cars.id = text;
    auto row_number = iter->second;
    model->item(row_number,0);
    cars.dataType = e_MessageType::e_MessageType_commnication;
    cars.name = ui->name->text().toStdString();
    cars.time = QTime::currentTime().toString().toStdString();
    cars.state = "Арендована";
    auto dat= cars.toString();
    std::cout<<dat<<std::endl;
    networker->sendMessage(std::move(dat));
}

void ClientWindow::run()
{
}

void ClientWindow::senRequest()
{
    CarStateMes carsRequest{.dataType = e_MessageType::e_GetFullData};
    auto mes = carsRequest.toString();
    networker->sendMessage(std::move(mes));
}
