#ifndef WALLET_H
#define WALLET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <qmath.h>

struct wall
{
    QString name;
    double vol = 0;
    double scal_vol = 0;
    bool targ = false;
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
    void del_token(const QString& tok);
    const QList<wall>* take_list_token();
    double get_sum_token(const QString& tok);

    void detect_pos();
    ~Wallet();


private:
    QList<wall> l_total_wall;
    Ui::Wallet *ui;
    bool in_diapazon(const int &center,const int &face,const int &in);
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    int sel = 0;
    void calculate();
    double kof;
    double sel_rad;
    int ws;
    int hs;
    int zerox;
    int zeroy;
    int xRad;
    int yRad;
    double xscale;
    double yscale;
    int left_face;
    int right_face;
    int up_face;
    int down_face;
    int mposX;
    int mposY;
    double X_;
    double Y_;
    QRectF pie;
signals:
    void target_piece(const QString& name_tok, const bool targ);

};

#endif // WALLET_H
