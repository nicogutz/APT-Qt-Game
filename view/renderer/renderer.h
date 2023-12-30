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

    inline static constexpr int m_cellSize = 50;

    // protected:
    //     QPixmap rotatePixmap(const QPixmap &originalPixmap, int direction);

protected:
    QPixmap rotatePixmap(const QPixmap &originalPixmap, int direction);

private:
    virtual GamePixmapItem *renderTile(QMap<DataRole, QVariant> object) = 0;
    virtual GamePixmapItem *renderDoorway(QMap<DataRole, QVariant> object) = 0;
    virtual GamePixmapItem *renderHealthPack(QMap<DataRole, QVariant> object) = 0;
    virtual GamePixmapItem *renderProtagonist(QMap<DataRole, QVariant> object) = 0;
    virtual GamePixmapItem *renderEnemy(QMap<DataRole, QVariant> object) = 0;
    virtual GamePixmapItem *renderPEnemy(QMap<DataRole, QVariant> object) = 0;
    virtual GamePixmapItem *renderMovingEnemy(QMap<DataRole, QVariant> object) = 0;
};

#endif // RENDERER_H
