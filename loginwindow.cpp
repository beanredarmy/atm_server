#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->label_3->setStyleSheet("QLabel { background-color : rgb(34, 62, 74) ; color : rgb(255, 255, 255); }");
    QFont labelFont = QFont("Roboto Mono",14);
    labelFont.setBold(1);
    ui->label_3->setFont(labelFont);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_buttonBox_accepted()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if(username == "root" && password =="root")
    {
        w = new MainWindow(this);
        w->show();
    } else
    {
        QMessageBox::warning(this,"Login","Thông tin đăng nhập không chính xác!");
        show();
    }
}
