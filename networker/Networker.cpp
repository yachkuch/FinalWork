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

#include <QMessageBox>
#include <QNetworkDatagram>
#include <QDebug>

void Networker::sendMessage(std::string message)
{
  message.push_back('\n');
  sendSocket->writeDatagram(message.data(),QHostAddress::LocalHost,(quint16) portSend);
}

void Networker::sendData(std::string data)
{
  emit dataRecieves(data);
}

void Networker::read()
{
  std::string recieve_string;
  std::cout<<"Данные пришли \n";
   while (recieveSoket->hasPendingDatagrams()) 
   {
    QNetworkDatagram datagram = recieveSoket->receiveDatagram();
    std::string datagramString = datagram.data().data();
    qDebug()<<datagramString.data();
    emit dataRecieves(std::move(datagramString));
    }
}

Networker::Networker(unsigned int portRecieve,unsigned int portSend, std::string ip_adress) :
portRecieve(portRecieve),portSend(portSend)
{
    recieveSoket = std::make_unique<QUdpSocket>(this);
    sendSocket = std::make_unique<QUdpSocket>(this);
    recieveSoket->bind(QHostAddress::LocalHost,(quint16) portRecieve);
    recieveSoket->open(QIODevice::ReadOnly);
    if (recieveSoket->isOpen())
    {
        connect(recieveSoket.get(),SIGNAL(readyRead()),this,SLOT(read()));
    } 
    else 
    {
        QMessageBox MB;
        MB.setText("Сокет приема не был открыт");
        MB.exec();
    }
    sendSocket->open(QIODevice::WriteOnly);
    if(!sendSocket->isOpen())
    {
        QMessageBox MB;
        MB.setText("Сокет посылки не был открыт");
        MB.exec();
    }
}
