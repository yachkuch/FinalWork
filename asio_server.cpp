#include "Networker.h"
#include "DataBaseWorker.h"
#include <cstdio>
#include <boost/asio/io_context.hpp>
#include <mainwindow.h>
#include <iostream>
#include <thread>
#include <QApplication>
// #include <process.h>
#include <QThread>


int main(int argc, char *argv[])
{
    QApplication apl(argc, argv);
    MainWindow window;
    QThread thread;
    window.show();

    // TODO: Добавить отправку текстового сообщения с ошибкой или сообщения ок
    boost::asio::io_context context;
    Networker net(context, 1337, "127.0.0.1");
    DataBaseWorker dbw;

    net.sig.connect(dbw);
    net.start_server();
    dbw.start_db();
    //context.run();
    return apl.exec();
}
