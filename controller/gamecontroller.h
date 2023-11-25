#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QGraphicsView>

#include <model/gameobjectmodel.h>

#include <view/gameview.h>

class GameController : public QGraphicsView {
    Q_OBJECT
public:
    GameController();

public slots:
    void characterMove();

private:
    QSharedPointer<GameObjectModel> m_model;
    QSharedPointer<GameView> m_view;
};

#endif // GAMECONTROLLER_H
