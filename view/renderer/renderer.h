#ifndef RENDERER_H
#define RENDERER_H

#include "model/gameobject.h"
#include "qpixmap.h"
#include <bits/shared_ptr.h>



class Renderer
{
public:
    Renderer();
    virtual ~Renderer() {}

    QPixmap renderGameObject(const GameObject& object) ;

private:
    virtual QPixmap renderTile(const GameObject& object) = 0;
    virtual QPixmap renderDoorway(const GameObject& object) = 0;
    virtual QPixmap renderHealthPack(const GameObject& object) = 0;
    virtual QPixmap renderProtagonist(const GameObject& object) = 0;
    virtual QPixmap renderEnemy(const GameObject& object) = 0;

};

#endif // RENDERER_H
