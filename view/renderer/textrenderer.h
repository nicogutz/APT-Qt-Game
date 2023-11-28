#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {

public:
    TextRenderer();

private:
    QPixmap renderTile(const GameObject &object) override;
    QPixmap renderDoorway(const GameObject &object) override;
    QPixmap renderHealthPack(const GameObject &object) override;
    QPixmap renderProtagonist(const GameObject &object) override;
    QPixmap renderEnemy(const GameObject &object) override;
};

#endif // TEXTRENDERER_H
