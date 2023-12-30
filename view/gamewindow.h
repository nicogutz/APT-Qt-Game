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
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    QSharedPointer<QWidget> a;
    std::shared_ptr<QWidget> b;

    void showInvalidCommandMessage();
    void showHelp();
    bool eventFilter(QObject *watched, QEvent *event) override;

    // GETTERS
    QSharedPointer<GameController> getController() { return m_controller; }
    Ui::GameWindow *getUI() { return m_ui; }
    QTimer *getTimer() { return m_timer; }

private:
    Ui::GameWindow *m_ui;
    QSharedPointer<GameController> m_controller;
    int m_startTime;
    int m_elapsedSeconds;
    QTimer *m_timer;

public slots:
    void updateTime();
    void updateLevel(unsigned int level, unsigned int enemies, unsigned int health_packs);
    void processCommand();
    void zoomBySlider(int value);

    void setSpriteView();
    void setTextualView();
    void setColorView();

    void togglePause();
    void gameOver();

protected:
    void keyPressEvent(QKeyEvent *event) override;

    // QObject interface
};
#endif // GAMEWINDOW_H
