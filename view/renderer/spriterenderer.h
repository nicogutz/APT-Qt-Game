#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

#include <QTimer>

class SpriteRenderer : public Renderer {
public:
    SpriteRenderer();

private:
    GamePixmapItem *renderTile(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderDoorway(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderHealthPack(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderProtagonist(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderEnemy(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderPEnemy(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderDeath(const QString &imagePath, int numOfFrames);
    GamePixmapItem *renderMovingEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderActor(const QString &imagePath, int cellSize);
    QPixmap renderActor(const QString &imagePath, int cellSize, int POVFrame, int numPOVs);
    int calculateFrame(int direction, int numPOVs);
};

#endif // SPRITERENDERER_H
