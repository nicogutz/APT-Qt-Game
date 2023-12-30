#include "view/renderer/colorrenderer.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QSharedPointer>
#include <QStyleFactory>
#include <QFile>

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
    QFile f(":qdarkstyle/light/lightstyle.qss");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    qApp->setStyleSheet(ts.readAll());

    qSetMessagePattern("%{function}(%{line}): %{message}");
    // Create the main classes of the gzme: GameWindow, GameView, GameController
    GameWindow w;
    auto gameController = w.getController();
    Ui::GameWindow *ui = w.getUI();

    // Connect Signals and slots
    QObject::connect(ui->textEdit, &QLineEdit::returnPressed, &w, &GameWindow::processCommand);
    QObject::connect(ui->quit_game, &QPushButton::clicked, &app, &QApplication::quit);
    QObject::connect(ui->rerun_game_2, &QPushButton::clicked, [] {
        QCoreApplication::quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    });
    w.show();
    return app.exec();

    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
