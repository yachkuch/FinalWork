#ifndef __NETWORKER_H_6RM5NKCO09GG__
#define __NETWORKER_H_6RM5NKCO09GG__
#include <boost/asio/ip/tcp.hpp>
#include <boost/signals2.hpp>
#include <memory>
#include <string>
#include <vector>
#include <QObject>

#include <QUdpSocket>


class Networker : public QObject
{

  Q_OBJECT

  public:

  Networker( unsigned int portRecieve,unsigned int portSend, std::string ip_adress = "");
  ~Networker() = default;

  void sendMessage(std::string message);
  void sendData(std::string data);
  
  private:

  std::unique_ptr<QUdpSocket> recieveSoket;
  std::unique_ptr<QUdpSocket> sendSocket;

  QByteArray data;

  unsigned int portRecieve;
  unsigned int portSend;

  private slots:
    void read();

  signals:  void dataRecieves(std::string data);

};


#endif // __NETWORKER_H_6RM5NKCO09GG__
