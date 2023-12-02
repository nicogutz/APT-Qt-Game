#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {

public:
    TextRenderer();

private:
    QPixmap renderTile(const QSharedPointer<GameObject> &object) override;
    QPixmap renderDoorway(const QSharedPointer<GameObject> &object) override;
    QPixmap renderHealthPack(const QSharedPointer<GameObject> &object) override;
    QPixmap renderProtagonist(const QSharedPointer<GameObject> &object) override;
    QPixmap renderEnemy(const QSharedPointer<GameObject> &object) override;
};

#endif // TEXTRENDERER_H
