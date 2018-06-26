#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include <QThreadPool>
#include <runnabledevproc.h>


class DeviceManager : public QObject
{
    Q_OBJECT
public:

    explicit DeviceManager(QObject *parent = nullptr);

    bool getIsLogedIn() const;


signals:

public slots:
    void processPendingDatagrams(QNetworkDatagram datagram);
    void sendRequestData();
    void sendRequestLogin();
    void setIsLogedIn(bool value);
private:
    unsigned short deviceID;
    QUdpSocket *udpSocket = nullptr;

    bool isLogedIn;
    QHostAddress deviceAddress;
    int devicePort;

};

#endif // DEVICEMANAGER_H
