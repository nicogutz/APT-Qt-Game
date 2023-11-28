#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

class SpriteRenderer : public Renderer {

public:
    SpriteRenderer();

private:
    QPixmap renderTile(const QSharedPointer<GameObject> object) override;
    QPixmap renderDoorway(const QSharedPointer<GameObject> object) override;
    QPixmap renderHealthPack(const QSharedPointer<GameObject> object) override;
    QPixmap renderProtagonist(const QSharedPointer<GameObject> object) override;
    QPixmap renderEnemy(const QSharedPointer<GameObject> object) override;
};

#endif // SPRITERENDERER_H
