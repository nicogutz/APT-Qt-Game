#include "renderer.h"
#include "qrandom.h"

#include <QPainter>
#include <QPropertyAnimation>

GamePixmapItem *Renderer::renderGameObjects(QList<QMap<DataRole, QVariant>> dataList) {
    auto *tile = renderGameObject(dataList[0]);
    renderGameObject(dataList[0], tile);

    for(const auto &data : dataList.mid(1, -1)) {
        auto *obj = renderGameObject(data);
        renderGameObject(data, obj);
        obj->setParentItem(tile);
    }
    return tile;
}

GamePixmapItem *Renderer::renderGameObject(QMap<DataRole, QVariant> data) {
    auto *item = new GamePixmapItem();
    item->setData((int)DataRole::Type, data[DataRole::Type]);
    return item;
}

void Renderer::renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) {
    if(data[DataRole::Path].toBool())
        item->setTint(QColor(0, 0, 255, 100), true);

    if(item->isActive()) {
        DataRole change = data[DataRole::LatestChange].value<DataRole>();
        ObjectType type = data[DataRole::Type].value<ObjectType>();

        switch(change) {
        case DataRole::Health:
            if((int)type > 49) {
                if(data[DataRole::Health].toInt()) {
                    item->addAnimation(animateHealth(data[DataRole::ChangeDirection].value<Direction>()));
                } else {
                    item->setSprite(animateHealthPack(data[DataRole::Health].toInt(), item));
                    item->updatePixmap();
                    break;
                }
            } else {
            }
            return;
        case DataRole::PoisonLevel:
            if(type == ObjectType::Tile) {
                item->setTint({21, 88, 21, data[DataRole::PoisonLevel].toInt() * 15}, true);
            }
            return;
        case DataRole::Strength:
            if(type == ObjectType::MovingEnemy) {
                item->animationGroup()->clear();
                item->setOpacity(1);
            }
            item->addAnimation(animateAttack(
              data[DataRole::Direction].toInt(),
              data[DataRole::LatestChange].value<Direction>() == Direction::Up));
            return;
        default:
            return;
        }
    }
}

QImage Renderer::animateHealthPack(int health, GamePixmapItem *item) {
    auto pixmap = item->pixmap();
    QPainterPath piePath;
    piePath.moveTo(pixmap.rect().center());
    piePath.arcTo(pixmap.rect(), 0, health * 10);

    QPixmap croppedPixmap(pixmap.size());
    croppedPixmap.fill(Qt::transparent);

    QPainter painter(&croppedPixmap);
    painter.setClipPath(piePath);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();
    return pixmap.toImage();
}

QPropertyAnimation *Renderer::animateHealth(Direction dir) {
    bool healthGain = (dir == Direction::Up);
    return animateTint({255 * !healthGain, 255 * healthGain, 0, 80});
}

QPropertyAnimation *Renderer::animateBounce() {
    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setPropertyName("pos");
    anim->setDuration(QRandomGenerator::global()->bounded(400, 600));
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
    anim->setLoopCount(1);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setEasingCurve(QEasingCurve::OutCubic);
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

QPixmap Renderer::rotatePixmap(const QPixmap &pixmap, int direction) {
    QTransform transformation;
    transformation.rotate(-direction + 90);
    return pixmap.transformed(transformation);
}

QImage Renderer::rotateImage(const QImage &image, int direction) {
    QTransform transformation;
    transformation.rotate(-direction + 90);
    return image.transformed(transformation);
}
