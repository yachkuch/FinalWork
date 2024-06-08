#include "Networker.h"
#include <cstdio>
#include <boost/asio/io_context.hpp>
#include <mainwindow.h>
#include <iostream>
#include <thread>
#include <QApplication>
// #include <process.h>
#include <QThread>
#include "Protocol.h"

int main(int argc, char *argv[])
{
    QApplication apl(argc, argv);
    MainWindow window;
    window.show();
    //boost::asio::io_context context;
    //Networker net(context, 1337, "127.0.0.1");
    //net.sig.connect(dbw);
    //net.start_server();
    apl.exec();
    //context.run();
    return 1;
}
