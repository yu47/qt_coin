#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QDebug>
#include <QTimer>
class Mycoin : public QPushButton
{
    Q_OBJECT
public:
    explicit Mycoin(QWidget *parent = nullptr);

    Mycoin( QString filename);

    int posX;
    int posY;
    bool flag;
    bool isAnimation  = true;
    QTimer* timer1;
    QTimer* timer2;


    void changecoin(int ms);
    void mousePressEvent(QMouseEvent *e) override;
    int max=8;
    int min=1;
signals:

};

#endif // MYCOIN_H
