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

    QPixmap renderGameObject(const QSharedPointer<GameObject>& object);

private:
    virtual QPixmap renderTile(const QSharedPointer<GameObject>& object) = 0;
    virtual QPixmap renderDoorway(const QSharedPointer<GameObject>& object) = 0;
    virtual QPixmap renderHealthPack(const QSharedPointer<GameObject>& object) = 0;
    virtual QPixmap renderProtagonist(const QSharedPointer<GameObject>& object) = 0;
    virtual QPixmap renderEnemy(const QSharedPointer<GameObject>& object) = 0;

};

#endif // RENDERER_H
