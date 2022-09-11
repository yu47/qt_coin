#include "mycoin.h"

//Mycoin::Mycoin(QWidget *parent) : QPushButton(parent)
//{

//}

Mycoin::Mycoin(QString butImg)
{
    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if(!ret)
    {
        qDebug() << butImg << "加载图片失败!";
    }

    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));


    timer1 = new QTimer(this);
    timer2 = new QTimer(this);


    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap coinimg;
        coinimg.load(QString(":/res/Coin000%1.png").arg(this->min++));
        this->setFixedSize(coinimg.width(),coinimg.height());
        this->setIcon(coinimg);
        this->setStyleSheet(("QPushButton{border:0px;}"));
        this->setIconSize(QSize(coinimg.width(),coinimg.height()));
        if(this->min > this->max){
            this->min = 1;
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,this,[=](){
        QPixmap coinimg;
        coinimg.load(QString(":/res/Coin000%1.png").arg(this->max--));
        this->setFixedSize(coinimg.width(),coinimg.height());
        this->setIcon(coinimg);
        this->setStyleSheet(("QPushButton{border:0px;}"));
        this->setIconSize(QSize(coinimg.width(),coinimg.height()));
        if(this->min > this->max){
            this->max = 8;
            timer2->stop();
        }
    });

}

void Mycoin::changecoin(int ms)
{
    if(!this->isAnimation){
        return;
    }
    if(this->flag){
        timer1->start(ms);
        this->flag=false;
    }
    else {
        timer2->start(ms);
        this->flag=true;
    }

}

void Mycoin::mousePressEvent(QMouseEvent *e)
{
//    if(this->isAnimation){
//        return;
//    }
    return QPushButton::mousePressEvent(e);
}
