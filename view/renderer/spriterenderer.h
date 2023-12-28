#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

#include <QTimer>

class SpriteRenderer : public Renderer {
public:
    SpriteRenderer();

private:
    QPixmap renderTile(QMap<DataRole, QVariant> object) override;
    QPixmap renderDoorway(QMap<DataRole, QVariant> object) override;
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object) override;
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object) override;
    QPixmap renderEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderActor(const QString& imagePath, int cellSize);
    QPixmap renderActor(const QString& imagePath, int cellSize, int POVFrame, int numPOVs);
    int calculateFrame(int direction, int numPOVs);
};

#endif // SPRITERENDERER_H
