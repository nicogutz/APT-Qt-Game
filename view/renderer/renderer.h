#ifndef RENDERER_H
#define RENDERER_H

#include "publicenums.h"
#include "qpixmap.h"
#include <QGraphicsPixmapItem>

class Renderer {
public:
    Renderer();
    virtual ~Renderer() {
    }

    QGraphicsPixmapItem *renderGameObjects(QList<QMap<DataRole, QVariant>> objectData);
    QPixmap renderGameObject(QMap<DataRole, QVariant> objectData);

    inline static constexpr int cellSize = 50;

protected:
    QPixmap rotatePixmap(const QPixmap &originalPixmap, int direction);

    virtual QPixmap renderTile(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderDoorway(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderHealthPack(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderProtagonist(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderEnemy(QMap<DataRole, QVariant> object) = 0;
};

#endif // RENDERER_H
