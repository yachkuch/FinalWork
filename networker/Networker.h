#ifndef __NETWORKER_H_6RM5NKCO09GG__
#define __NETWORKER_H_6RM5NKCO09GG__
#include <boost/asio/ip/tcp.hpp>
#include <boost/signals2.hpp>
#include <memory>
#include <string>
#include <vector>

class Networker;
/**
 * @brief Класс вычитывателя соединения
 *
 */
struct Session : std::enable_shared_from_this<Session> {
  Session(boost::asio::io_context &context,std::shared_ptr<boost::asio::ip::tcp::socket> socket,
        Networker &net)
      : context(context), socket(std::move(socket)),net(net)
         {}
  void run();
  boost::asio::io_context &context;
  std::shared_ptr<boost::asio::ip::tcp::socket> socket;
  std::string received_line;
  Networker &net;
  std::vector<char> unused_bytes;
};
///////////////////////////////////////////////////////////
/// @brief Networker класс сервера
///
class Networker final {
public:
  explicit Networker(boost::asio::io_context &con, unsigned int port,
                     std::string ip_adress = "");
  virtual ~Networker();

  void start_server();

  void sendData(std::string data);

  void operator()(std::string string);
  boost::signals2::signal<std::string(std::string string)> sig;

private:

  void handleAccept(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
  unsigned int port_ = 0;
  std::vector<char> unusedBytes;
  std::string ip_ = "127.0.0.1";
  boost::asio::ip::tcp::acceptor *acceptor = nullptr;
  std::shared_ptr<boost::asio::ip::tcp::socket> pSocket;
  boost::asio::io_context &context;
};



#endif // __NETWORKER_H_6RM5NKCO09GG__
