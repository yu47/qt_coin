#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "qpainter.h"
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent *);
    QMediaPlayer *player;

private slots:
    void on_actionquit_triggered();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
