#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

#include <QPropertyAnimation>
#include <QTimer>

class SpriteRenderer : public Renderer {
public:
    SpriteRenderer() {
        m_characters = QImage(":/images/characters.png");
        m_tiles = QImage(":/images/tiles.png");

        m_charSize = QSize(m_characters.width() / CHAR_MAX_X, m_characters.height() / CHAR_MAX_Y);
        m_tileSize = QSize(m_tiles.width() / TILE_COUNT, m_tiles.width() / TILE_COUNT);
    }

    void renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) override;
    GamePixmapItem *renderGameObject(QMap<DataRole, QVariant> data) override;

    enum SpriteSettings {
        TILE_COUNT = 21,
        CHAR_MAX_X = 10,
        CHAR_MAX_Y = 8,
    };

    struct CharacterData {
        QPoint alive;
        QPoint dead;
    };

    inline static const QMap<ObjectType, CharacterData> m_charMap = {
      {ObjectType::Protagonist, {{7, 0}, {9, 1}}},
      {ObjectType::MovingEnemy, {{7, 2}, {4, 3}}},
      {ObjectType::PoisonEnemy, {{7, 4}, {4, 5}}},
      {ObjectType::Enemy, {{7, 6}, {2, 7}}},
    };

private:
    QPropertyAnimation *animateTint(GamePixmapItem *item, QColor final, QColor initial = {0, 0, 0, 0});
    int calculateFrame(QVariant direction, int numPOVs);
    void animateDeath(GamePixmapItem *item);
    void animateHealth(GamePixmapItem *item, Direction dir);
    void animatePoison(GamePixmapItem *item, int level);

    QRect getTileRect(QMap<DataRole, QVariant> data);
    QImage sliceFrames(QImage image, QLine diagonal, QPoint frameSize);

    QImage m_tiles, m_characters;
    QSize m_charSize, m_tileSize;
    QRect getCharacterRect(ObjectType type);
};

#endif // SPRITERENDERER_H
