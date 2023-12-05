#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

class SpriteRenderer : public Renderer {

public:
    SpriteRenderer();

private:


    // Renderer interface
private:
    QPixmap renderTile(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderDoorway(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderHealthPack(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderProtagonist(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderEnemy(const QMap<GameObject::DataRole, const QVariant> &object) override;
};

#endif // SPRITERENDERER_H
