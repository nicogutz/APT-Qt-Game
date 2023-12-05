#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QSharedPointer>

#include <controller/gamecontroller.h>

#include <QElapsedTimer>
#include <QKeyEvent>

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

    QSharedPointer<GameController> getController();


private:

    Ui::GameWindow* ui;
    QSharedPointer<GameController> controller;
    int startTime;
    int elapsedSeconds;
    QTimer *timer;
    int paused;


public slots:
    void updateTime(bool active);


protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // GAMEWINDOW_H
