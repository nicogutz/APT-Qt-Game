#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {

public:
    TextRenderer();

private:


    // Renderer interface
private:
    QPixmap renderTile(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderDoorway(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderHealthPack(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderProtagonist(const QMap<GameObject::DataRole, const QVariant> &object) override;
    QPixmap renderEnemy(const QMap<GameObject::DataRole, const QVariant> &object) override;
};

#endif // TEXTRENDERER_H
