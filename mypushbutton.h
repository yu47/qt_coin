#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg ,QString PreeImg = "");

    void zoom1();
    void zoom2();

    QString normalImg;
    QString PreeImg;

signals:

};

#endif // MYPUSHBUTTON_H
