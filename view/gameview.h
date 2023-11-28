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

    // Method to create scene with list of list of GameObjects
    void createScene(const QList<QList<GameObject*>>& gameObjects, Renderer* renderer = nullptr);

    // Method to update a specific tile
    void updateTile(const GameObject& gameObject, int x, int y);

    // Method to change the renderer
    void setRenderer(Renderer* newRenderer);

private:
    int m_rows, m_columns;
    Renderer* m_renderer; // Renderer instance to generate QPixmap from GameObjects

    // Store the graphical representation of each GameObject
    QList<QList<QGraphicsPixmapItem*>> m_tiles;
};

#endif // GAMEVIEW_H
