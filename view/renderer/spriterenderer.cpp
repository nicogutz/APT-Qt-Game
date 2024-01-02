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
            if((int)type > 99) {
                if(data[DataRole::Health].toInt()) {
                    animateHealth(item, data[DataRole::ChangeDirection].value<Direction>());
                } else {
                    animateDeath(item);
                }
            }
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
    return ((direction.toInt() / 45 + 2) % (numPOVs + 1));
}

void SpriteRenderer::animateDeath(GamePixmapItem *item) {
    QPropertyAnimation *deathAnimation = new QPropertyAnimation(item, "frame");
    QPoint frame = m_charMap[item->data((int)DataRole::Type).value<ObjectType>()].dead;
    deathAnimation->setParent(item);
    deathAnimation->setDuration(250 * frame.x());
    deathAnimation->setStartValue(QPoint(0, 1));
    deathAnimation->setEndValue(QPoint(frame.x(), 1));
    deathAnimation->setLoopCount(1);
    deathAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SpriteRenderer::animateHealth(GamePixmapItem *item, Direction dir) {
    bool healthGain = (dir == Direction::Up);
    animateTint(item, {255 * !healthGain, 255 * healthGain, 0, 80})->start(QAbstractAnimation::DeleteWhenStopped);
}

void SpriteRenderer::animatePoison(GamePixmapItem *item, int level) {
    animateTint(item, {0, 255, 0, level * 3})->start(QAbstractAnimation::DeleteWhenStopped);
}

QPropertyAnimation *SpriteRenderer::animateTint(GamePixmapItem *item, QColor initial, QColor final) {
    QPropertyAnimation *healthAnimation = new QPropertyAnimation(item, "tint");
    healthAnimation->setParent(item);
    healthAnimation->setDuration(400);
    healthAnimation->setStartValue(initial);
    healthAnimation->setEndValue(final);
    healthAnimation->setEasingCurve(QEasingCurve::SineCurve);
    healthAnimation->setLoopCount(1);
    return healthAnimation;
}
