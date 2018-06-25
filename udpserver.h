#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QList>
#include <QMap>
#include "devicemanager.h"
#define DEFAULT_BIND_PORT 4568
class UDPServer : public QObject
{
    Q_OBJECT
public:
    explicit UDPServer(QObject *parent = nullptr);

signals:

public slots:
    void processPendingDatagrams();
private:
    QUdpSocket *udpSocket = nullptr;
    bool isLogedIn;
    QMap<unsigned short, DeviceManager*> DeviceList;
};

#endif // UDPSERVER_H
