#include "chooselevelscene.h"
//#include "qpixmap.h"
#include "mypushbutton.h"
#include <QPixmap>
#include <QPainter>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(350,630);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币-选择关卡");
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu* startmMenu = bar->addMenu("开始");
    QAction* quitAction = startmMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });



    MyPushButton* coin_back = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    coin_back->setParent(this);
    coin_back->move(this->width()*0.68,this->height()*0.88);

    connect(coin_back,&MyPushButton::clicked,[=](){
        emit this->choosesignals();
//        this->hide();
//        this->show();
    });


    for (int i=0;i < 20 ; i++) {
        MyPushButton *levebtn = new MyPushButton(":/res/LevelIcon.png");
        levebtn->setParent(this);
        levebtn->move(35 + (i%4)*70 , 140+ (i/4)*75);

        QLabel *levenum = new QLabel();
        levenum->setText(QString::number(i+1));
        levenum->setParent(this);
        levenum->move(35 + (i%4)*70 , 138+ (i/4)*75);
        levenum->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        levenum->setFixedSize(levebtn->width(),levebtn->height());
        levenum->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this) ;
    QPixmap *pix = new QPixmap;
    pix->load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),*pix);
}
