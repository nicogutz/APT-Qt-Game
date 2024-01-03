#include "spriterenderer.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <iostream>

GamePixmapItem *SpriteRenderer::renderGameObject(QMap<DataRole, QVariant> data) {
    auto *item = new GamePixmapItem();
    item->setData((int)DataRole::Type, data[DataRole::Type]);

    ObjectType type = data[DataRole::Type].value<ObjectType>();
    switch(type) {
    case ObjectType::Tile:
        // We could also save the whole tile sprite since
        // images are shared data in Qt. I'm more partial to this.
        item->setSprite(m_tiles.copy(getTileRect(data)));
        item->updatePixmap();
        return item;
    case ObjectType::Doorway:
        item->setSprite(QImage(":/images/doorway.png"));
        item->updatePixmap();
        return item;
    case ObjectType::HealthPack:
        item->setSprite(QImage(":/images/health_pack.png"));
        item->updatePixmap();
        return item;
    default:
        item->setSprite(m_characters.copy(getCharacterRect(type)));
        item->setFrameDimension(m_charSize);
        item->updatePixmap();
        return item;
    }
}

void SpriteRenderer::renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) {
    DataRole change = data[DataRole::LatestChange].value<DataRole>();
    ObjectType type = data[DataRole::Type].value<ObjectType>();
    if(item->isActive()) {
        switch(change) {
        case DataRole::Direction:
            item->setFrame({calculateFrame(data[DataRole::Direction], m_charMap[type].alive.x()),
                            item->frame().y()});
            return;
        case DataRole::Health:
            if((int)type > 49) {
                if(data[DataRole::Health].toInt()) {
                    item->addAnimation(animateHealth(data[DataRole::ChangeDirection].value<Direction>()));
                } else {
                    item->animationGroup()->clear();
                    item->addAnimation(animateDeath(m_charMap[item->data((int)DataRole::Type).value<ObjectType>()].dead));
                    item->setTint({0, 0, 0, 0});
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
    }
}

QRect SpriteRenderer::getTileRect(QMap<DataRole, QVariant> data) {
    float energyLevel = round(data[DataRole::Energy].toFloat() * 19);
    int tile = energyLevel == INFINITY ? TILE_COUNT - 1 : energyLevel;
    return {tile * m_tileSize.width(), 0, m_tileSize.width(), m_tileSize.height()};
}

QRect SpriteRenderer::getCharacterRect(ObjectType type) {
    CharacterData data = m_charMap[type];
    int maxX = data.alive.x() > data.dead.x() ? data.alive.x() : data.dead.x();

    return {0, data.alive.y() * m_charSize.height(),
            m_charSize.width() * maxX, m_charSize.height() * 2};
}

int SpriteRenderer::calculateFrame(QVariant direction, int numPOVs) {
    return (((direction.toInt() / 45) + 2) % (numPOVs + 1));
}

QPropertyAnimation *SpriteRenderer::animateDeath(QPoint frame) {
    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setPropertyName("frame");
    anim->setDuration(250 * frame.x());
    anim->setStartValue(QPoint(0, 1));
    anim->setEndValue(QPoint(frame.x(), 1));
    anim->setLoopCount(1);
    return anim;
}

QPropertyAnimation *SpriteRenderer::animateHealth(Direction dir) {
    bool healthGain = (dir == Direction::Up);
    return animateTint({255 * !healthGain, 255 * healthGain, 0, 80});
}

QPropertyAnimation *SpriteRenderer::animateAttack(int dir, bool attacking) {
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

QPropertyAnimation *SpriteRenderer::animateTint(QColor final, QColor initial) {
    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setPropertyName("tint");
    anim->setDuration(400);
    anim->setStartValue(initial);
    anim->setEndValue(final);
    anim->setEasingCurve(QEasingCurve::SineCurve);
    anim->setLoopCount(1);
    return anim;
}
