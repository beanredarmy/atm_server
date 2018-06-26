#include "udpserver.h"

UDPServer::UDPServer(QObject *parent) : QObject(parent)
{
    qDebug() << "create UDP server";
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress("192.168.1.10"),DEFAULT_BIND_PORT, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    DeviceManager *device1 = new DeviceManager();
    DeviceManager *device2 = new DeviceManager();
    DeviceManager *device3 = new DeviceManager();

    DeviceList.insert(1,device1);
    DeviceList.insert(2,device2);
    DeviceList.insert(3,device3);

    QThreadPool::globalInstance()->setMaxThreadCount(5);

}
void UDPServer::processPendingDatagrams()
{
    qDebug() << "server read data";
    QNetworkDatagram datagram;
    QByteArray datagramByteArr;
    unsigned short deviceID;
    QDataStream dataStream(&datagramByteArr, QIODevice::ReadOnly);

    while (udpSocket->hasPendingDatagrams()) {
        datagram = udpSocket->receiveDatagram();
        datagramByteArr = datagram.data();
        dataStream >> deviceID;
        DeviceList.value(deviceID)->processPendingDatagrams(datagram);

    }
}
