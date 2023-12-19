#ifndef RENDERER_H
#define RENDERER_H

#include "model/gameobject.h"
#include "qpixmap.h"
#include <bits/shared_ptr.h>
#include <QGraphicsPixmapItem>

class Renderer {
public:
    Renderer();
    virtual ~Renderer() {
    }

    QGraphicsPixmapItem *
    renderGameObject(const QVector<QMap<GameObject::DataRole, QVariant>> &dt_ls);
    inline static constexpr int cellSize = 50;

private:
    virtual QPixmap renderTile(QMap<GameObject::DataRole, QVariant> object) = 0;
    virtual QPixmap renderDoorway(QMap<GameObject::DataRole, QVariant> object) = 0;
    virtual QPixmap renderHealthPack(QMap<GameObject::DataRole, QVariant> object) = 0;
    virtual QPixmap renderProtagonist(QMap<GameObject::DataRole, QVariant> object) = 0;
    virtual QPixmap renderEnemy(QMap<GameObject::DataRole, QVariant> object) = 0;
};

#endif // RENDERER_H
