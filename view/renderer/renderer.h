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
    virtual QPixmap renderTile(const QMap<GameObject::DataRole, const QVariant>& object) = 0;
    virtual QPixmap renderDoorway(const QMap<GameObject::DataRole, const QVariant>& object) = 0;
    virtual QPixmap renderHealthPack(const QMap<GameObject::DataRole, const QVariant>& object) = 0;
    virtual QPixmap renderProtagonist(const QMap<GameObject::DataRole, const QVariant>& object) = 0;
    virtual QPixmap renderEnemy(const QMap<GameObject::DataRole, const QVariant>& object) = 0;
};

#endif // RENDERER_H
