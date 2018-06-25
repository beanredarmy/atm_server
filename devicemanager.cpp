#include "devicemanager.h"

DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost,DEFAULT_BIND_PORT, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    isLogedIn = false;
}

void DeviceManager::readLoginInfor(login_data loginData)
{
    switch (deviceID) {
    case 1:
        if(strcmp(loginData.username, "device1") == 0
                && strcmp(loginData.password, "thietbi1") == 0)
            isLogedIn = true;
        else isLogedIn = false;
        break;
    case 2:
        if(strcmp(loginData.username, "device2") == 0
                && strcmp(loginData.password, "thietbi2") == 0)
            isLogedIn = true;
        else isLogedIn = false;
    case 3:
        if(strcmp(loginData.username, "device3") == 0
                && strcmp(loginData.password, "thietbi3") == 0)
            isLogedIn = true;
        else isLogedIn = false;
    default:
        break;
    }
}

void DeviceManager::readData(sensor_data sensorData)
{

}

void DeviceManager::sendRequestData()
{

}

void DeviceManager::sendRequestLogin()
{

}

void DeviceManager::processPendingDatagrams(QNetworkDatagram datagram)
{
    define_data defineData;
    QByteArray datagramByteArr = datagram.data();
    QDataStream dataStream(&datagramByteArr, QIODevice::ReadOnly);
    defineData.deSerialize(dataStream);
    deviceID = defineData.device_id;
    deviceAddress = datagram.senderAddress();
    devicePort = datagram.senderPort();
    if(isLogedIn)
    {
        switch (defineData.packet_type) {
        case 1: // if packet type is login
            sendRequestData();
            break;
        case 2: // if packet type is data
            sensor_data sensorData;
            sensorData.deSerialize(dataStream);
            readData(sensorData);
            break;
        default:
            break;
        }
    } else
    {
        switch (defineData.packet_type) {
        case 1: // if packet type is login
            login_data loginData;
            loginData.deSerialize(dataStream);
            readLoginInfor(loginData);
            break;
        case 2: // if packet type is data
            sendRequestLogin();
            break;
        default:
            break;
        }
    }

}
