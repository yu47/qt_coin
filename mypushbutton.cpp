#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMouseEvent>
MyPushButton::MyPushButton(QString normalImg, QString PreeImg)
{
    this->normalImg = normalImg;
    this->PreeImg = PreeImg;
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug() << "加载图片失败";
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

}



void MyPushButton::zoom1()
{

    QPropertyAnimation *animation1 = new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();

}

void MyPushButton::zoom2()
{
    QPropertyAnimation * animation1 =  new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();

}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->PreeImg != ""){
        QPixmap pix;
        bool ret = pix.load(this->PreeImg);
        if(!ret){
            qDebug() << this->PreeImg << "图片加载失败！";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setIcon(pix);
        this->setStyleSheet("QpushButton{border:0}");
        this->setIconSize(QSize(pix.width(),pix.height()));



    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->PreeImg != ""){
        QPixmap pix;
        bool ret = pix.load(this->normalImg);
        if(!ret){
            qDebug() << this->normalImg << "图片加载失败！";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setIcon(pix);
        this->setStyleSheet("QpushButton{border:0}");
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    return QPushButton::mouseReleaseEvent(e);
}
