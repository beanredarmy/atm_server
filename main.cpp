#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include <udpserver.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow g;
    g.show();
    //UDPServer newUDPServer;
    return a.exec();
}
