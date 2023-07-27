#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wallet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void add_token();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Wallet* _wal;
    void configuration();
};
#endif // MAINWINDOW_H
