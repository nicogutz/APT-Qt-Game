#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QObject>

class GameView : public QGraphicsScene
{
public:
    explicit GameView(QObject *parent = nullptr);
};

#endif // GAMEVIEW_H
