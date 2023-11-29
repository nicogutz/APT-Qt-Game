#ifndef COLORRENDERER_H
#define COLORRENDERER_H

#include "renderer.h"

class ColorRenderer : public Renderer
{
public:
    ColorRenderer();
    ~ColorRenderer();;

private:
    QPixmap renderTile(const GameObject &object) override;
    QPixmap renderDoorway(const GameObject &object) override;
    QPixmap renderHealthPack(const GameObject &object) override;
    QPixmap renderProtagonist(const GameObject &object) override;
    QPixmap renderEnemy(const GameObject &object) override;
};


#endif // COLORRENDERER_H
