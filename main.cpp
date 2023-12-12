#include "ui_gamewindow.h"
#include "view/gamewindow.h"
#include "controller/gamecontroller.h"
#include "view/gameview.h"


#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

  // Create the main classes of the gzme: GameWindow, GameView, GameController
    GameWindow w;
    auto widget = QSharedPointer<QWidget>(new QWidget(&w));
    auto gameController = w.getController();

  // Get classes' variables
    QTimer* timer = w.getTimer();
    Ui::GameWindow* ui = w.getUI();


  // Connect Signals and slots
    QObject::connect(gameController.data(), &GameController::levelChanged, &w, &GameWindow::updateLevel);

    QObject::connect(ui->textEdit, &QLineEdit::returnPressed, &w, &GameWindow::processCommand);


    w.show();




  // Calling different signals and methods for testing

    //emit gameController->levelChangedSig(2);

    return a.exec();


}
