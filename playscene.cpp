#include "playscene.h"
#include <QPixmap>
#include <QPainter>
#include <QMenu>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QDebug>
#include <QLabel>
#include "dataconfig.h"
#include "mycoin.h"
#include <QEasingCurve>
#include <QPropertyAnimation>
PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{




}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);

}

bool PlayScene::iswind()
{
    for (int k=0; k < 4; k++) {
        for (int n=0; n < 4; n++) {
            if(coinBtn[k][n]->flag == 0) return false;
        }
    }
    return true;
}

void PlayScene::ischange()
{
    if(wind){
        for (int k=0; k < 4; k++) {
            for (int n=0; n < 4; n++) {
                coinBtn[k][n]->isAnimation = false;
            }
        }
    }
}





PlayScene::PlayScene(int index)
{
    this->index = index;
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setFixedSize(350,650);

    QMenuBar *menu = menuBar();
    setMenuBar(menu);
    QMenu* startMenu = menu->addMenu("开始");
    QAction *close = startMenu->addAction("退出");
    connect(close,&QAction::triggered,[=](){
        this->close();
    });
    this->setWindowTitle("第"+QString::number(this->index)+"关卡");

    MyPushButton *back = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    back->setParent(this);
    back->move(this->width()*0.68,this->height()*0.88);
    connect(back,&MyPushButton::clicked,[=](){
        backSound->play();
        emit this->playsignal();
    });


    QPixmap pix;
    for(int i = 0 ; i<4 ; i++){
        for(int j=0 ; j <4 ; j++){
            pix.load(":/res/BoardNode(1).png");
            QLabel *label = new QLabel();
            label->setScaledContents(true);
            label->setGeometry(0,0,pix.width()*1.2,pix.height()*1.2);

//            label->setFixedSize(pix.width(),pix.height());

            label->setPixmap(pix);
            label->setParent(this);
            label->move(50+i*60,205+j*60);




        }
    }

    dataConfig data;
    QString img;

    QLabel *windimg = new QLabel();
    QPixmap winpix;
    winpix.load(":/res/LevelCompletedDialogBg.png");
    windimg->setGeometry(0,0,winpix.width(),winpix.height());
    windimg->setPixmap(winpix);
    windimg->setParent(this);
    windimg->move(this->width()*0.5 - windimg->width()*0.5,-this->height()*0.2);


    for(int i = 0 ; i<4 ; i++){
        for(int j=0 ; j <4 ; j++){
            if(data.mData[index][i][j] == 1){
               img = ":/res/Coin0001.png";
            }
            else {
               img = ":/res/Coin0008.png";
            }
            Mycoin *coin = new Mycoin(img);
            coin->setParent(this);
            coin->move(58+i*60,214+j*60);
            coin->posX = i;
            coin->posY = j;
            coin->flag = data.mData[index][i][j];
            this->gameArray[i][j] = data.mData[index][i][j];
            coinBtn[i][j] = coin;
            connect(coin,&Mycoin::clicked,[=](){

                flipSound->play();

                coin->changecoin(30);
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改

                if(i > 0 && i < 3){
                    coinBtn[i + 1][j]->changecoin(50);
                    coinBtn[i - 1][j]->changecoin(50);
                }
                else if (i == 0) {
                    coinBtn[i + 1][j]->changecoin(50);
                }
                else if (i == 3) {
                    coinBtn[i - 1][j]->changecoin(50);
                }


                if(j > 0 && j < 3){
                    coinBtn[i][j + 1]->changecoin(50);
                    coinBtn[i][j - 1]->changecoin(50);
                }
                else if (j == 0) {
                    coinBtn[i][j + 1]->changecoin(50);
                }
                else if (j == 3) {
                    coinBtn[i][j - 1]->changecoin(50);
                }
                wind = iswind();
                if(wind){
                    ischange();
                    qDebug() << "游戏胜利";

                    winSound->play();

                    windimg->raise();

                    QPropertyAnimation * animation1 =  new QPropertyAnimation(windimg,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(windimg->x(),windimg->y(),windimg->width(),windimg->height()));
                        animation1->setEndValue(QRect(windimg->x(),windimg->y()+this->height()*0.7 - windimg->height()*0.5,windimg->width(),windimg->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                    }
            });

        }
    }



}

