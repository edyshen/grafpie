#include "wallet.h"
#include "ui_wallet.h"



Wallet::Wallet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wallet)
{
    sel_rad = 360 / (2 * M_PI);
    kof = 0;
    sel = 0;
    ui->setupUi(this);
    this->setMouseTracking(true);
    this->resize(600,600);
    l_total_wall.clear();
    wall tmp;
    tmp.vol = 10;



}
void Wallet::sel_tok(const QString &tok)    // ВЫДЕЛЕНИЕ СЕГМЕНТА ПО ЗАПРОСУ СПИСКА!!!!!
{
    //////////////////////// ДОПИЛИТЬ!
}
void Wallet::add_token(wall &tok)
{
    l_total_wall.append(tok);
    calculate();
    this->update();
}
void Wallet::mouseMoveEvent(QMouseEvent *event)
{
    this->update();
}
void Wallet::del_token(const QString &tok)
{
    for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i++)
    {
        if(i->name == tok)
        {
            l_total_wall.erase(i);
            break;
        }
    }
    calculate();
    this->update();
}
double Wallet::get_sum_token(const QString &tok)
{
    for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i++)
    {
        if(i->name == tok)
        {
            return i->vol;
        }
    }
    return 0;
}
void Wallet::paintEvent(QPaintEvent *event)
{
    QPainter wall(this);
    int ws = this->width();
    int hs = this->height();
    QPen pen;
    wall.setPen(pen);
    pen.setWidth(0);

    QRectF pie (ws / 8, hs / 8, ws - (ws/8) *2, hs - (hs /8)*2);  // Размер Круга графика!
    int zerox = int(pie.center().x());
    int zeroy = int(pie.center().y());
    int xRad = int(pie.width() / 2);
    int yRad = int(pie.height() / 2);
    double xscale = 1 / double(xRad);
    double yscale = 1 / double(yRad);
    int left_face = zerox - xRad;
    int right_face = zerox + xRad;
    int up_face = zeroy - yRad;
    int down_face = zeroy + yRad;
    int mposX = this->mapFromGlobal(QCursor::pos()).x();
    int mposY = this->mapFromGlobal(QCursor::pos()).y();
    double X_ = (mposX - zerox) * xscale;
    double Y_ = (zeroy - mposY) * yscale;
    if(in_diapazon(zerox, left_face, mposX) && in_diapazon(zeroy, up_face, mposY)) // левый верхний угол
    {        
        if(qSqrt(pow(X_, 2) + pow(Y_, 2)) <= 1)
        {
            double arctng;
            arctng = (M_PI/2) + qAtan( (-X_) / (Y_));
            sel = int(std::round(arctng * sel_rad));

        }
    }
    if(in_diapazon(zerox, right_face, mposX) && in_diapazon(zeroy, up_face, mposY)) // Правый верхний угол
    {        
        if(qSqrt(pow(X_, 2) + pow(Y_, 2)) <= 1)
        {
            double arctng;
            arctng = qAtan( Y_ / X_);
            sel = int(std::round(arctng * sel_rad));

        }
    }
    if(in_diapazon(zerox, left_face, mposX) && in_diapazon(zeroy, down_face, mposY)) //Левый нижний угол
    {       
        if(qSqrt(pow(X_, 2) + pow(Y_, 2)) <= 1)
        {
            double arctng;
            arctng = M_PI + qAtan( Y_ / X_);
            sel = int(std::round(arctng * sel_rad));
            if(sel == 90) sel = 270;

        }
    }
    if(in_diapazon(zerox, right_face, mposX) && in_diapazon(zeroy, down_face, mposY)) //Правый нижний угол
    {
        if(qSqrt(pow(X_, 2) + pow(Y_, 2)) <= 1)
        {
            double arctng;
            arctng = M_PI + M_PI_2 + qAtan( X_ / (-Y_));
            sel = int(std::round(arctng * sel_rad));
            if(sel == 180)sel = 0;

        }
    }
    ///////////////////////////////////   Отрисовка Графика по созданым данным

    int rate = 0;
    int rate_= 0;
    for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i++)
    {
        rate_ += int(std::round(i->scal_vol));
        if(in_diapazon(rate, rate_, sel))
        {
            pen.setColor(Qt::red);
            pen.setWidth(2);
            wall.setPen(pen);
            wall.setBrush(Qt::white);
            wall.drawPie(pie, rate * 16 , int(std::round(i->scal_vol) * 16));
        }else
        {
            pen.setWidth(0);
            pen.setColor(Qt::black);
            wall.setPen(pen);
            wall.setBrush(QColor(255,55,150));
            wall.drawPie(pie, rate * 16 , int(std::round(i->scal_vol) * 16));
        }
        rate = rate_;
    }
}
const QList<wall>* Wallet::take_list_token()
{
    return &l_total_wall;
}

void Wallet::calculate()
{
    kof = 0;
    for(int i = 0; i < l_total_wall.size(); i++)
    {
        kof =  l_total_wall.at(i).vol + kof;
    }
    kof = 360 / kof;

    for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i++)
    {
        i->scal_vol = i->vol * kof;
    }

}

bool Wallet::in_diapazon(int &center, int &face, int &in)
{
    if(center > face)
    {
        if( in <= center && in > face) return true;
    }
    if(center < face)
    {
        if(in >= center && in < face) return true;
    }
    return false;
}


Wallet::~Wallet()
{
    delete ui;
}
