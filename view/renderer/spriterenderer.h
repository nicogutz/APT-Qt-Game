#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

class SpriteRenderer : public Renderer {

public:
    SpriteRenderer();

private:
    // Renderer interface
private:
    QPixmap
    renderTile(QMap<GameObject::DataRole, QVariant> object) override;
    QPixmap renderDoorway(
        QMap<GameObject::DataRole, QVariant> object) override;
    QPixmap renderHealthPack(
        QMap<GameObject::DataRole, QVariant> object) override;
    QPixmap renderProtagonist(
        QMap<GameObject::DataRole, QVariant> object) override;
    QPixmap
    renderEnemy(QMap<GameObject::DataRole, QVariant> object) override;
};

#endif // SPRITERENDERER_H
