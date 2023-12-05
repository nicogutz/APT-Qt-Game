#ifndef COLORRENDERER_H
#define COLORRENDERER_H

#include "renderer.h"

class ColorRenderer : public Renderer
{
public:
    ColorRenderer();

private:

    // Renderer interface
private:
    QPixmap renderTile(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderDoorway(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderHealthPack(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderProtagonist(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderEnemy(const QMap<GameObject::DataRole, const QVariant> &object) override;

};


#endif // COLORRENDERER_H
