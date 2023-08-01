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
void Wallet::mouseDoubleClickEvent(QMouseEvent *event)
{
    detect_pos();
    if(sel != -1)
    {
        int frst = 0;
        int fend = 0;
        for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i++)
        {
            fend += int(std::round(i->scal_vol));
            if(in_diapazon(frst,fend,sel))
            {
                if(i->targ == false)
                {
                    i->targ = true;
                    emit target_piece(i->name, i->targ);
                }else
                {
                    i->targ = false;
                    emit target_piece(i->name, i->targ);
                }
            }
            frst = fend;
        }
        this->update();
    }
}
void Wallet::itemclick(QListWidgetItem* item)
{
    if(item->isSelected())
    {
        for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i ++)
        {
            if(item->text() == i->name) i->targ = true;
        }
    }else
    {
        for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i ++)
        {
            if(item->text() == i->name) i->targ = false;
        }
    }
    this->update();
}
void Wallet::add_token(wall &tok)  ////РАБОТАЕТ НЕ ПРАВИЛЬНО! ДОПИЛИТЬ!!! подсчитывает только колличество токенов
{
    for(QList<wall>::iterator i = l_total_wall.begin(); i < l_total_wall.end(); i++)
    {
        if(i->name == tok.name)
        {
            qDebug() << i->vol;
            i->vol += tok.vol;
            qDebug() << i->vol;
            return;
        }
    }
    l_total_wall.append(tok);
    this->update();
}
void Wallet::mouseMoveEvent(QMouseEvent *event)
{
    detect_pos();
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
void Wallet::detect_pos()
{
    ws = this->width();
    hs = this->height();
    pie = QRectF(ws / 8, hs / 8, ws - (ws/8) *2, hs - (hs /8)*2);  // Размер Круга графика!
    zerox = int(pie.center().x());
    zeroy = int(pie.center().y());
    xRad  = int(pie.width() / 2);
    yRad  = int(pie.height() / 2);
    xscale = 1 / double(xRad);
    yscale = 1 / double(yRad);
    left_face  = zerox - xRad;
    right_face = zerox + xRad;
    up_face    = zeroy - yRad;
    down_face  = zeroy + yRad;
    mposX      = this->mapFromGlobal(QCursor::pos()).x();
    mposY      = this->mapFromGlobal(QCursor::pos()).y();
    X_      = (mposX - zerox) * xscale;
    Y_      = (zeroy - mposY) * yscale;
    sel = -1;
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
    if(sel != -1)
    {
        this->update();
    }
}
void Wallet::paintEvent(QPaintEvent *event)
{
    detect_pos();
    ///////////////////////////////////   Отрисовка Графика по созданым данным
    calculate();
    QPainter wall(this);
    int rate = 0;
    int rate_= 0;
    for(auto i = l_total_wall.begin(); i != l_total_wall.end(); i++)
    {
        rate_ += int(std::round(i->scal_vol));
        int piece = 360 - rate;
        if(in_diapazon(rate, rate_, sel))
        {
            wall.setBrush(Qt::yellow);
            wall.drawPie(pie, rate * 16 , piece * 16);
        }
        else
        {
            if(i->targ == true)
            {
                wall.setBrush(QColor(250,250,250));
                wall.drawPie(pie, rate * 16 , piece * 16);
            }else
            {
                wall.setBrush(QColor(250,0,0));
                wall.drawPie(pie, rate * 16 , piece * 16);
            }
        }
        rate = rate_;
    }
    emit after_render(&l_total_wall);
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

bool Wallet::in_diapazon(const int &center,const int &face,const int &in)
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
    qDebug() << "the end";
}
