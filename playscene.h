#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
#include <QSound>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int index);

    int gameArray[4][4];

    Mycoin* coinBtn[4][4];

    bool wind = false;
    void paintEvent(QPaintEvent *);

    bool iswind();
    void ischange();


    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);

    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    QSound *backSound = new QSound(":/res/TapButtonSound.wav",this);

    int index;
signals:
    void playsignal();
};

#endif // PLAYSCENE_H
