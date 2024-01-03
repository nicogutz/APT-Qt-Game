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
    virtual GamePixmapItem *renderGameObject(QMap<DataRole, QVariant> objectData);
    virtual void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item);

    QPixmap rotatePixmap(const QPixmap &originalPixmap, int direction);

protected:
    inline static constexpr int CELL_SIZE = 50;

private:
    virtual QPixmap renderTile(QMap<DataRole, QVariant> object) {};
    virtual QPixmap renderDoorway(QMap<DataRole, QVariant> object) {};
    virtual QPixmap renderHealthPack(QMap<DataRole, QVariant> object) {};
    virtual QPixmap renderProtagonist(QMap<DataRole, QVariant> object) {};
    virtual QPixmap renderEnemy(QMap<DataRole, QVariant> object) {};
    virtual QPixmap renderPEnemy(QMap<DataRole, QVariant> object) {};
    virtual QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object) {};

    QPropertyAnimation *animateTint(QColor final, QColor initial = {0, 0, 0, 0});
    QPropertyAnimation *animateAttack(int dir, bool attacking);
    QPropertyAnimation *animateHealth(Direction dir);
};

#endif // RENDERER_H
