
#include "view/gamewindow.h"
#include "world.h"


#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QMainWindow w;
    auto widget = QSharedPointer<QWidget>(new QWidget(&w));
    auto txt = QSharedPointer<QLabel>(new QLabel(widget.get()));
    txt->setText("Hello");
    QLabel* bs = new QLabel();
    bs->setText("hello");
    w.show();

    //connect.keyPressEvent();

    //connect(w, &w::key, receiver, &ReceiverClass::slotName);


    return a.exec();
}
