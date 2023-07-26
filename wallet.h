#ifndef WALLET_H
#define WALLET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <qmath.h>

struct wall
{
    char name[4]{'n','u','l','l'};
    double vol = 0;
    double scal_vol = 0;
};

namespace Ui {
class Wallet;
}

class Wallet : public QWidget
{
    Q_OBJECT

public:
    explicit Wallet(QWidget *parent = nullptr);
    void add_token(wall &tok);
    ~Wallet();

private:
    QList<wall> l_total_wall;
    Ui::Wallet *ui;
    bool in_diapazon(int &center, int &face, int &in);
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    int sel = 0;
    void calculate();
    double kof;
    double sel_rad;

};

#endif // WALLET_H
