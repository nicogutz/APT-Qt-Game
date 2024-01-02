#ifndef RENDERER_H
#define RENDERER_H

#include "publicenums.h"
#include "qpixmap.h"
#include "view/gamepixmapitem.h"

class Renderer {
public:
    Renderer();
    virtual ~Renderer() {
    }

    GamePixmapItem *renderGameObjects(QList<QMap<DataRole, QVariant>> objectData);
    GamePixmapItem *renderGameObject(QMap<DataRole, QVariant> objectData);
    virtual void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item);

    QPixmap rotatePixmap(const QPixmap &originalPixmap, int direction);

protected:
    inline static constexpr int CELL_SIZE = 50;

private:
    virtual QPixmap renderTile(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderDoorway(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderHealthPack(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderProtagonist(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderEnemy(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderPEnemy(QMap<DataRole, QVariant> object) = 0;
    virtual QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object) = 0;
};

#endif // RENDERER_H
