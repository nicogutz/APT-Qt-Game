#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

class SpriteRenderer : public Renderer {

public:
    SpriteRenderer();

private:
    QPixmap renderTile(const GameObject &object) override;
    QPixmap renderDoorway(const GameObject &object) override;
    QPixmap renderHealthPack(const GameObject &object) override;
    QPixmap renderProtagonist(const GameObject &object) override;
    QPixmap renderEnemy(const GameObject &object) override;
};

#endif // SPRITERENDERER_H
