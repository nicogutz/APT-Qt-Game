
#include "view/gamewindow.h"


#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    GameWindow w;
    auto widget = QSharedPointer<QWidget>(new QWidget(&w));
    //auto txt = QSharedPointer<QLabel>(new QLabel(widget.get()));
    //txt->setText("Hello");
    //QLabel* bs = new QLabel();
    //bs->setText("hello");

    //w.getController()->characterMove(GameObject::Direction::Up);

    w.show();


    return a.exec();
}
