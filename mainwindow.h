#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wallet.h"
#include <QPushButton>

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
    void list_tok();
    void del_token();
    void item_click();
    void after_render(QList<wall>* total_tok);
public slots:
    void selected_item(const QString& name, const bool& targ);

private:
    Ui::MainWindow *ui;
    Wallet* _wal;
    void configuration();
};
#endif // MAINWINDOW_H
