#include "mainwindow.h"
#include <QApplication>
#include <udpserver.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    UDPServer newUDPServer;
    return a.exec();
}
