#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _wal(new Wallet)
{
    ui->setupUi(this);
    ui->grid_pie->addWidget(_wal);
}
void MainWindow::add_token()
{
    wall tok;
//    tok.name =
}

MainWindow::~MainWindow()
{
    delete ui;
}

