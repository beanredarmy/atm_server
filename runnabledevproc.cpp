#include "runnabledevproc.h"

RunnableDevProc::RunnableDevProc(bool isLogedIn, QNetworkDatagram datagram) : isLogedIn(isLogedIn), datagram(datagram)
{

}

void RunnableDevProc::readLoginInfor(unsigned short deviceID, login_data loginData)
{
    qDebug() << "read login info";

    //it will be checked and work in database

    switch (deviceID) {
    case 1:
        if(strcmp(loginData.username, "device1") == 0
                && strcmp(loginData.password, "password1") == 0)
        {
            isLogedIn = true;
            qDebug() << "login successful!";
        }

        else isLogedIn = false;
        break;
    case 2:
        if(strcmp(loginData.username, "device2") == 0
                && strcmp(loginData.password, "password2") == 0)
            isLogedIn = true;
        else isLogedIn = false;
    case 3:
        if(strcmp(loginData.username, "device3") == 0
                && strcmp(loginData.password, "password2") == 0)
            isLogedIn = true;
        else isLogedIn = false;
    default:
        break;
    }

    emit returnLoginState(isLogedIn);
}

void RunnableDevProc::readData(unsigned short deviceID, sensor_data sensorData)
{
    //it will written into database
}

void RunnableDevProc::run()
{
    qDebug() << "processPendingDatagrams ";
    define_data defineData;
    QByteArray datagramByteArr = datagram.data();
    QDataStream dataStream(&datagramByteArr, QIODevice::ReadOnly);
    defineData.deSerialize(dataStream);
    unsigned short deviceID = defineData.device_id;

    if(isLogedIn)
    {
        switch (defineData.packet_type) {
        case 1: // if packet type is login
            sendRequestData();
            break;
        case 2: // if packet type is data
            sensor_data sensorData;
            sensorData.deSerialize(dataStream);
            readData(deviceID, sensorData);
            break;
        default:
            break;
        }
    } else
    {
        qDebug() << "chua login";
        switch (defineData.packet_type) {
        case 1: // if packet type is login
            qDebug() << "day la goi login";
            login_data loginData;
            loginData.deSerialize(dataStream);
            readLoginInfor(deviceID, loginData);

            break;
        case 2: // if packet type is data
            sendRequestLogin();
            break;
        default:
            break;
        }
    }
}
