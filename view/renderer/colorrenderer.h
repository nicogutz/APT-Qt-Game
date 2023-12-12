#ifndef COLORRENDERER_H
#define COLORRENDERER_H

#include "renderer.h"

class ColorRenderer : public Renderer {
public:
    ColorRenderer();

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

#endif // COLORRENDERER_H
