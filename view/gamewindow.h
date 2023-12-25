#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QSharedPointer>

#include <controller/gamecontroller.h>

#include <QElapsedTimer>
#include <QKeyEvent>
#include <QProcess>
#include <QTimer>
#include <iostream>
#include <QTime>
#include <qgraphicsitem.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow{
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();
    QSharedPointer<QWidget> a;
    std::shared_ptr<QWidget> b;

    QSharedPointer<GameController> getController(){return controller;}
    Ui::GameWindow* getUI(){return ui;}
    QTimer* getTimer(){return timer;}

    void showInvalidCommandMessage();
    void showHelp();


private:

    Ui::GameWindow* ui;
    QSharedPointer<GameController> controller;
    int start_time;
    int elapsed_seconds;
    QTimer *timer;
    int paused;


public slots:
    void updateTime(bool active);
    void updateLevel(unsigned int level);
    void processCommand();
    void zoomBySlider(int value);




protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // GAMEWINDOW_H
