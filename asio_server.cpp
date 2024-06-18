#include <boost/asio/io_context.hpp>
#include <mainwindow.h>
#include <iostream>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication apl(argc, argv);
    MainWindow window;
    window.show();
    apl.exec();
    return 1;
}
