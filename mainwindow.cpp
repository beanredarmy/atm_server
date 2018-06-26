#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpOtherUi();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpOtherUi()
{
    ui->softwareNameLabel->setStyleSheet("QLabel { background-color : rgb(34, 62, 74) ; color : rgb(255, 255, 255); }");
    QFont labelFont = QFont("Roboto Mono",18);
    labelFont.setBold(1);
    ui->softwareNameLabel->setFont(labelFont);

    QLabel *lbl1 = new QLabel("HOME");
    QLabel *lbl2 = new QLabel("CHI TIẾT");

    ui->mainTabWidget->setFont( QFont("Lato",12));
    ui->mainTabWidget->setTabIcon(0,QIcon(":/img/icon/overview.png"));
    ui->mainTabWidget->setTabIcon(1,QIcon(":/img/icon/detail.png"));
    ui->mainTabWidget->tabBar()->setTabButton(0,QTabBar::LeftSide,lbl1);
    ui->mainTabWidget->tabBar()->setTabButton(1,QTabBar::LeftSide,lbl2);

}
