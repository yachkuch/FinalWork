
#include <boost/asio/io_context.hpp>

#include <mainwindow.h>
#include <iostream>
#include <thread>
#include <QApplication>

#include <QTimer>



int main(int argc, char *argv[])
{
    boost::asio::io_context context;
    QApplication apl(argc, argv);
    MainWindow window(context);
    window.show();
    apl.exec();
    return 1;
}
