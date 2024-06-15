#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <QApplication>
#include "clientwindow.h"
namespace asio = boost::asio;
int main(int argc, char *argv[]) 
{
  asio::io_context context;
  QApplication apl(argc, argv);
  ClientWindow window(context);
  window.show();
  apl.exec();
  return 1;
}