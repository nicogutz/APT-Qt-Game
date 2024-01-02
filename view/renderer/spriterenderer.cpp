#include "spriterenderer.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <iostream>

void SpriteRenderer::renderGameObject(QMap<DataRole, QVariant> object, GamePixmapItem *item) {
    ObjectType type = object[DataRole::Type].value<ObjectType>();
    if(item->isActive()) {
        item->setFrame({calculateFrame(object[DataRole::Direction], m_charMap[type].alive.x()), item->frame().y()});
        return;
    }
}

QRect SpriteRenderer::getTileRect(QMap<DataRole, QVariant> object) {
    float energyLevel = round(object[DataRole::Energy].toFloat() * 19);
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

GamePixmapItem *SpriteRenderer::renderGameObject(QMap<DataRole, QVariant> object) {
    ObjectType type = object[DataRole::Type].value<ObjectType>();
    auto *item = new GamePixmapItem();
    switch(type) {
    case ObjectType::Tile:
        item->setSprite(m_tiles.copy(getTileRect(object)));
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
