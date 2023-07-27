#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QValidator"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _wal(new Wallet)
{
    ui->setupUi(this);
    configuration();
    ui->grid_pie->addWidget(_wal);
    connect(ui->OK, &QPushButton::clicked, this, &MainWindow::add_token);

}
void MainWindow::add_token()
{
    if(ui->name->text() != "" && ui->price->text() != "" && ui->value->text() != "")
    {

    }
    else{}
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::configuration()
{
    QRegExp exp("[A-Za-z]{4}");
    QDoubleValidator* dec = new QDoubleValidator;
    dec->setNotation(QDoubleValidator::StandardNotation);
    ui->name->setValidator(new QRegExpValidator(exp));
    ui->price->setValidator(dec);
    ui->value->setValidator(dec);
}

