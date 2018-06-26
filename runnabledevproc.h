#ifndef RUNNABLEDEVPROC_H
#define RUNNABLEDEVPROC_H

#include <QObject>
#include<QRunnable>
#include<QNetworkDatagram>
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


class RunnableDevProc : public QObject, public QRunnable
{
    Q_OBJECT
public:
    RunnableDevProc(bool isLogedIn, QNetworkDatagram datagram);
    void run();
    void readLoginInfor(unsigned short deviceID, login_data loginData);
    void readData(unsigned short deviceID, sensor_data sensorData);
signals:
    void returnLoginState(bool isLogedIn);
    void sendRequestData();
    void sendRequestLogin();
private:
    QNetworkDatagram datagram;
    bool isLogedIn;
};

#endif // RUNNABLEDEVPROC_H
