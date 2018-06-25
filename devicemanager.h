#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDataStream>

#define DEFAULT_BIND_PORT 4568
#define NUMDEV 3
struct define_data {
    unsigned short device_id;
    unsigned char packet_type;
    void deSerialize(QDataStream &in) {
        in >> device_id;
        in >> packet_type;
    }
};

struct sensor_data{
  unsigned char tem_sensor;
  unsigned char hum_sensor;
  unsigned char tem_sensor_ex;
  unsigned char hum_sensor_ex;
  unsigned int timestamp;

  void deSerialize(QDataStream &in) {
      in >> tem_sensor;
      in >> hum_sensor;
      in >> tem_sensor_ex;
      in >> hum_sensor_ex;
      in >> timestamp;

  }
};

struct login_data {

    char *username;
    char *password;

    void deSerialize(QDataStream &in) {
        in >> username;
        in >> password;
    }
};



class DeviceManager : public QObject
{
    Q_OBJECT
public:

    explicit DeviceManager(QObject *parent = nullptr);
    void readLoginInfor(login_data loginData);
    void readData(sensor_data sensorData);
    void checkLoginInfor();
    void run();
    void sendRequestData();
    void sendRequestLogin();
signals:

public slots:
    void processPendingDatagrams(QNetworkDatagram datagram);
private:
    unsigned short deviceID;
    QUdpSocket *udpSocket = nullptr;
    bool isLogedIn;
    QHostAddress deviceAddress;
    int devicePort;
};

#endif // DEVICEMANAGER_H
