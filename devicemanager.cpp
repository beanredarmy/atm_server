#include "devicemanager.h"

DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{
   // udpSocket = new QUdpSocket(this);
  //  udpSocket->bind(QHostAddress::LocalHost,DEFAULT_BIND_PORT, QUdpSocket::ShareAddress);
   // connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    isLogedIn = false;
}



void DeviceManager::sendRequestData()
{

}

void DeviceManager::sendRequestLogin()
{

}

bool DeviceManager::getIsLogedIn() const
{
    return isLogedIn;
}

void DeviceManager::setIsLogedIn(bool value)
{
    isLogedIn = value;
}

void DeviceManager::processPendingDatagrams(QNetworkDatagram datagram)
{
    deviceAddress = datagram.senderAddress();
    devicePort = datagram.senderPort();

    RunnableDevProc *runnableDevProc = new RunnableDevProc(isLogedIn, datagram);
    runnableDevProc->setAutoDelete(true);
    connect(runnableDevProc, SIGNAL(returnLoginState(bool)), this, SLOT(setIsLogedIn(bool)), Qt::QueuedConnection);
    connect(runnableDevProc, SIGNAL(sendRequestData()), this, SLOT(sendRequestData()), Qt::QueuedConnection);
    connect(runnableDevProc, SIGNAL(sendRequestLogin()), this, SLOT(sendRequestLogin()), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(runnableDevProc);
}

