#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QObject>
#include <QList>
#include "model/gameobject.h"
#include "view/renderer/renderer.h"

class GameView : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameView(int rows, int columns, QObject *parent = nullptr);

    void createScene(const QList<QList<QSharedPointer<GameObject>>>& gameObjects, QSharedPointer<Renderer> renderer = nullptr);

    void updateTile(const QSharedPointer<GameObject>& gameObject);

    void setRenderer(QSharedPointer<Renderer> newRenderer);

private:
    int m_rows, m_columns;
    QSharedPointer<Renderer> m_renderer;

    // Store the graphical representation of each GameObject
    QList<QList<QSharedPointer<QGraphicsPixmapItem>>> m_tiles;
};

#endif // GAMEVIEW_H
