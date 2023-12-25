#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

class SpriteRenderer : public Renderer {
public:
    SpriteRenderer();
    QPixmap renderTile(QMap<DataRole, QVariant> object) override;
    QPixmap renderDoorway(QMap<DataRole, QVariant> object) override;
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object) override;
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object) override;
    QPixmap renderEnemy(QMap<DataRole, QVariant> object) override;
};

#endif // SPRITERENDERER_H
