#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {

public:
    TextRenderer();

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
    QPixmap renderCharacter(QString, int, int);
};

#endif // TEXTRENDERER_H
