#include "mainscene.h"
#include "ui_mainscene.h"
#include <qpixmap.h>
#include <qpainter.h>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include <QTimer>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    this->setFixedSize(350,630);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");

    MyPushButton* star_btn = new MyPushButton(":/res/MenuSceneStartButton.png");
    star_btn->setParent(this);
    star_btn->move(this->width() * 0.5 - star_btn->width()*0.5,this->height()*0.7);

    ChooseLevelScene *chooseScene = new ChooseLevelScene;

    connect(star_btn,&MyPushButton::clicked,[=](){
//        star_btn->move(this->width() *0.5 - star_btn->width() * 0.45 , this->height() * 0.72);
//        star_btn->setFixedSize(star_btn->width()*0.9 , star_btn->height()*0.9);
//        star_btn->setSizePolicy()
        star_btn->zoom1();
        star_btn->zoom2();
        player = new QMediaPlayer();
        player->setMedia(QUrl("qrc:/res/myDouDZ.wav"));
        player->setVolume(60);
        player->play();
        QTimer::singleShot(300,this,[=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });


    connect(chooseScene,&ChooseLevelScene::choosesignals,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->close();
        this->show();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");

    pix = pix.scaled(pix.width() * 0.5 ,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}


void MainScene::on_actionquit_triggered()
{
    this->close();
}
