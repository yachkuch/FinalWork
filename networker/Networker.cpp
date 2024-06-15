#include "Networker.h"
#include <array>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

void Session::run()
{
  std::array<char, 150> buff;
  socket->async_receive(
      boost::asio::buffer(buff),
      [&, unused_bytes_ref = std::ref(this->unused_bytes),
       self = shared_from_this()](const boost::system::error_code &er,
                                  size_t bytes) mutable
      {
        if (er)
        {
          std::cout << er.message() << "\n";
          return;
        }
        if (bytes == 0)
        {
          std::cout << "Received 0\n";
          return;
        }
        std::string recieve_string;
        if (!unused_bytes_ref.get().empty())
        {
          std::cout << "Parapapa \n";
          std::abort();
        }
        for (int i = 0; i < bytes - 1; i++)
        {
          recieve_string.push_back(buff.at(i));
        }
        net.sendData(std::move(recieve_string));
        self->run();
      });
}

Networker::Networker(boost::asio::io_context &con, unsigned int port,
                     std::string ip_adress)
    : context(con)
{
  this->port_ = port;
  this->ip_ = ip_adress;
}

void Networker::start_server()
{
  namespace asio = boost::asio;

  asio::ip::tcp::endpoint endpoint(asio::ip::make_address_v4(ip_), port_);
  acceptor = new asio::ip::tcp::acceptor{context, endpoint};
  pSocket =
      std::make_shared<asio::ip::tcp::socket>(asio::ip::tcp::socket(context));
  acceptor->async_accept(*pSocket,
                         boost::bind(&Networker::handleAccept, this, pSocket));
  std::cout << "Server start \n";
}

void Networker::start_client()
{
  pSocket =
      std::make_shared<boost::asio::ip::tcp::socket>(boost::asio::ip::tcp::socket(context));
  bool is_connected = true;
  while (true)
  {
    try
    {
      pSocket->connect(
          boost::asio::ip::tcp::endpoint{boost::asio::ip::make_address_v4(ip_), port_});
      auto ses = std::make_shared<Session>(context, socket, *this);
      ses->run();
      break;
    }
    catch (...)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "Подключение не произошло, повторная попытка \n";
      continue;
    }
  }
}

void Networker::sendMessage(std::string message)
{
  message.push_back('\n');
  if (!pSocket)
    return;
  boost::system::error_code ec;
  auto send_n = pSocket->send(boost::asio::buffer(message), {}, ec);
  assert(!ec);
}

void Networker::sendData(std::string data)
{
  emit dataRecieves(data);
}

void Networker::handleAccept(
    std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
  std::cout << "New connection" << std::endl;
  auto ses = std::make_shared<Session>(context, std::move(socket), *this);
  ses->run();
}

void Networker::operator()(std::string string)
{
}

Networker::~Networker() {}