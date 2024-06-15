#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <thread>

#include "Networker.h"
#include "Protocol.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <QPushButton>

ClientWindow::ClientWindow(boost::asio::io_context &context, QWidget *parent) : QMainWindow(parent), context(context),
                                                                                networker(std::make_shared<Networker>(context, 1337, std::string("127.0.0.1"))),
                                                                                ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    connect(networker.get(), &Networker::dataRecieves, this, &ClientWindow::setTableData);
    networker->start_client();
    run();
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
}

ClientWindow::~ClientWindow()
{
    delete ui;
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
    ;
    auto iter = row_to_index.find(index);
    if (iter == row_to_index.end())
    {
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

void ClientWindow::run()
{
    auto ping = [](boost::asio::io_context &context)
    {
        while (true)
        {
            context.poll();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };
    std::thread a(ping, std::ref(context));
    a.detach();
}

void ClientWindow::senRequest()
{
    CarStateMes carsRequest{.dataType = e_MessageType::e_GetFullData};
    auto mes = carsRequest.toString();
    networker->sendMessage(std::move(mes));
}
