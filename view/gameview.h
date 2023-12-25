#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QObject>
#include <QList>
#include "view/renderer/renderer.h"

class GameView : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GameView(int rows, int columns, QObject *parent = nullptr);

    void createScene(const QList<QList<QList<QMap<DataRole, QVariant>>>> &gameObjects,
                     QSharedPointer<Renderer> renderer = nullptr);

    void setRenderer(QSharedPointer<Renderer> newRenderer);

private:
    int m_rows, m_columns;
    QSharedPointer<Renderer> m_renderer;

    // Store the graphical representation of each GameObject
    QList<QList<QSharedPointer<QGraphicsPixmapItem>>> m_tiles;

public slots:
    void dataChanged(QMap<DataRole, QVariant> objectData);
};

#endif // GAMEVIEW_H
