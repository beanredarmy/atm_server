#include "udpserver.h"

UDPServer::UDPServer(QObject *parent) : QObject(parent)
{
    qDebug() << "create UDP server";
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(DEFAULT_BIND_PORT, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    DeviceManager *device1;
    DeviceManager *device2;
    DeviceManager *device3;

    DeviceList.insert(1,device1);
    DeviceList.insert(2,device2);
    DeviceList.insert(3,device3);
}

void UDPServer::processPendingDatagrams()
{
    qDebug() << "server read data";
    QByteArray datagram;
    unsigned short deviceID;
    QDataStream dataStream(&datagram, QIODevice::ReadOnly);

    while (udpSocket->hasPendingDatagrams()) {
        datagram = udpSocket->receiveDatagram().data();
        dataStream >> deviceID;
        DeviceList.value(deviceID)->processPendingDatagrams(udpSocket->receiveDatagram());

    }
}
