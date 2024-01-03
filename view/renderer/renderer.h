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

protected:
    QImage animateHealthPack(int health, GamePixmapItem *item);
    QPropertyAnimation *animateTint(QColor final, QColor initial = {0, 0, 0, 0});
    QPropertyAnimation *animateAttack(int dir, bool attacking);
    QPropertyAnimation *animateBounce();
    QPropertyAnimation *animateHealth(Direction dir);
    QPropertyAnimation *animateHide();
};

#endif // RENDERER_H
