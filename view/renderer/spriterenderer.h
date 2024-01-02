#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

#include <QTimer>

class SpriteRenderer : public Renderer {
public:
    SpriteRenderer() {
        m_characters = QImage(":/images/characters.png");
        m_tiles = QImage(":/images/tiles.png");
    }
    void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) override;

    enum SpriteSettings {
        TILE_COUNT = 21,
        TILE_SIZE = 32,
    };

private:
    QPixmap renderTile(QMap<DataRole, QVariant> object) override;
    QPixmap renderDoorway(QMap<DataRole, QVariant> object) override;
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object) override;
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object) override;
    QPixmap renderEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object) override;
    int calculateFrame(int direction, int numPOVs);
    QPixmap renderActor(const QString &imagePath, int cellSize, int POVFrame, int numPOVs);
    QPixmap renderActor(const QString &imagePath, int cellSize);

    QImage m_tiles, m_characters;
};

#endif // SPRITERENDERER_H
