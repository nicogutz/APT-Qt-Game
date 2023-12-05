#ifndef COLORRENDERER_H
#define COLORRENDERER_H

#include "renderer.h"

class ColorRenderer : public Renderer
{
public:
    ColorRenderer();
    ~ColorRenderer();;

private:
    QPixmap renderTile(const QSharedPointer<GameObject> &object) override;
    QPixmap renderDoorway(const QSharedPointer<GameObject> &object) override;
    QPixmap renderHealthPack(const QSharedPointer<GameObject> &object) override;
    QPixmap renderProtagonist(const QSharedPointer<GameObject> &object) override;
    QPixmap renderEnemy(const QSharedPointer<GameObject> &object) override;
};


#endif // COLORRENDERER_H
