#include "view/renderer/colorrenderer.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QSharedPointer>

#include <model/gameobject.h>

#include "ui_gamewindow.h"
#include "view/gamewindow.h"
#include "controller/gamecontroller.h"
#include "model/modelfactory.h"

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <iostream>
#include <QProcess>
#include <view/renderer/textrenderer.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qSetMessagePattern("%{function}(%{line}): %{message}");
    // Create the main classes of the gzme: GameWindow, GameView, GameController
    GameWindow w;
    w.setStyleSheet("background-color: white");

    auto gameController = w.getController();
    Ui::GameWindow *ui = w.getUI();

    ObjectModelFactory factory;
    auto world = factory.createModel(":/images/worldmap.png", 1, 1, 0.25f);

    // Connect Signals and slots
    QObject::connect(gameController.data(), &GameController::levelChanged, &w, &GameWindow::updateLevel);
    QObject::connect(ui->textEdit, &QLineEdit::returnPressed, &w, &GameWindow::processCommand);
    QObject::connect(ui->quit_game, &QPushButton::clicked, &app, &QApplication::quit);
    QObject::connect(ui->rerun_game_2, &QPushButton::clicked, [] { QProcess::startDetached(qApp->arguments()[0], qApp->arguments()); });

    w.show();
    return app.exec();

    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
