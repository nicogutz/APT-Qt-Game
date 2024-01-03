#include "renderer.h"

#include <QPropertyAnimation>

Renderer::Renderer() {
}

GamePixmapItem *Renderer::renderGameObjects(QList<QMap<DataRole, QVariant>> objectDataList) {
    auto *tile = renderGameObject(objectDataList[0]);
    tile->setData((int)DataRole::Type, objectDataList[0][DataRole::Type]);

    for(const auto &data : objectDataList.mid(1, -1)) {
        auto *obj = renderGameObject(data);
        obj->setData((int)DataRole::Type, data[DataRole::Type]);
        obj->setParentItem(tile);
    }
    return tile;
}

GamePixmapItem *Renderer::renderGameObject(QMap<DataRole, QVariant> data) {
    auto *obj = new GamePixmapItem();
    obj->setData((int)DataRole::Type, data[DataRole::Type]);

    renderGameObject(data, obj);
    return obj;
}

void Renderer::renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) {
    if(item->isActive()) {
        DataRole change = data[DataRole::LatestChange].value<DataRole>();
        ObjectType type = data[DataRole::Type].value<ObjectType>();

        switch(change) {
        case DataRole::Health:
            if((int)type > 49) {
                if(data[DataRole::Health].toInt()) {
                    item->addAnimation(animateHealth(data[DataRole::ChangeDirection].value<Direction>()));
                } else {
                    break;
                }
            }
            return;
        case DataRole::PoisonLevel:
            if(type == ObjectType::Tile) {
                item->setTint({21, 88, 21, data[DataRole::PoisonLevel].toInt() * 15}, true);
            }
            return;
        case DataRole::Strength:
            item->addAnimation(animateAttack(
              data[DataRole::Direction].toInt(),
              data[DataRole::LatestChange].value<Direction>() == Direction::Up));
            return;
        case DataRole::Path:
            item->setTint(QColor(0, 0, 255, 100), true);
            return;
        default:
            return;
        }
    } else {
        switch(data[DataRole::Type].value<ObjectType>()) {
        case ObjectType::Tile:
            item->setPixmap(renderTile(data));
            break;
        case ObjectType::Doorway:
            item->setPixmap(renderDoorway(data));
            break;
        case ObjectType::HealthPack:
            item->setPixmap(renderHealthPack(data));
            break;
        case ObjectType::Protagonist:
            item->setPixmap(renderProtagonist(data));
            break;
        case ObjectType::Enemy:
            item->setPixmap(renderEnemy(data));
            break;
        case ObjectType::PoisonEnemy:
            item->setPixmap(renderPEnemy(data));
            break;
        case ObjectType::MovingEnemy:
            item->setPixmap(renderMovingEnemy(data));
            break;
        default:
            item->setPixmap(renderEnemy(data));
            break;
        }
    }
}

QPropertyAnimation *Renderer::animateHealth(Direction dir) {
    bool healthGain = (dir == Direction::Up);
    return animateTint({255 * !healthGain, 255 * healthGain, 0, 80});
}

QPropertyAnimation *Renderer::animateBounce() {
    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setPropertyName("pos");
    anim->setDuration(500);
    anim->setLoopCount(-1);
    anim->setStartValue(QPointF(0, 0));
    anim->setEndValue(QPointF(0, 3));
    anim->setEasingCurve(QEasingCurve::OutInBounce);
    return anim;
}
QPropertyAnimation *Renderer::animateHide() {
    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setPropertyName("opacity");
    anim->setDuration(2000);
    anim->setLoopCount(-1);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::SineCurve);
    return anim;
}

QPropertyAnimation *Renderer::animateAttack(int dir, bool attacking) {
    double angle = attacking ? dir : (dir + 180) % 360;
    QLineF line({0, 0}, {1, 0});
    QTransform transformation;
    transformation.rotate(angle);
    line = transformation.map(line);

    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setPropertyName("scaling");
    anim->setDuration(200);
    anim->setStartValue(line.p1());
    anim->setEndValue(line.p2());
    anim->setEasingCurve(QEasingCurve::SineCurve);
    anim->setLoopCount(1);
    return anim;
}

QPropertyAnimation *Renderer::animateTint(QColor final, QColor initial) {
    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setPropertyName("tint");
    anim->setDuration(400);
    anim->setStartValue(initial);
    anim->setEndValue(final);
    anim->setEasingCurve(QEasingCurve::SineCurve);
    anim->setLoopCount(1);
    return anim;
}
QPixmap Renderer::rotatePixmap(const QPixmap &originalPixmap, int direction) {
    QTransform transformation;
    transformation.rotate(-direction + 90);
    return originalPixmap.transformed(transformation);
}
