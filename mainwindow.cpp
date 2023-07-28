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
    connect(ui->DELET, &QPushButton::clicked, this, &MainWindow::del_token);
    connect(ui->list_token, &QListWidget::itemClicked, this, &MainWindow::item_click);


}
void MainWindow::del_token()
{
   if(ui->list_token->currentItem() != nullptr)
   {
       qDebug() << ui->list_token->currentItem()->text();
       _wal->del_token(ui->list_token->currentItem()->text());
       list_tok();

   }else{qDebug() << "NON";}
}
void MainWindow::list_tok()
{
    const QList<wall>* list_wallet = _wal->take_list_token();
    ui->list_token->clear();
    for(auto i = list_wallet->begin(); i != list_wallet->end(); i++)
    {
        qDebug() << i->name;
        QListWidgetItem* tmp = new QListWidgetItem(i->name);
        ui->list_token->addItem(tmp);
        _wal->update();
    }
}
void MainWindow::item_click()
{
    qDebug() << "clicked";
    ui->label_sum_tok->setText("Sum the Token  " + QString::number(_wal->get_sum_token(ui->list_token->currentItem()->text())));
    _wal->sel_tok(ui->list_token->currentItem()->text());

}
void MainWindow::add_token()
{
    if(ui->name->text() != "" && ui->price->text() != "" && ui->value->text() != "")
    {
        wall tmp;
        tmp.vol = ui->value->text().toDouble() * ui->price->text().toDouble();
        tmp.name = ui->name->text();
        _wal->add_token(tmp);
        ui->name->clear();
        ui->price->clear();
        ui->value->clear();
        list_tok();

    }
    else{
        qDebug() << "false";
    }
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

