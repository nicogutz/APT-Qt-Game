#include "colorrenderer.h"
#include "qpixmap.h"

ColorRenderer::ColorRenderer()
{}
int cellSize = 50;

QPixmap ColorRenderer::renderTile(const QMap<GameObject::DataRole, const QVariant> &object)
{
    int energyLevel = object[GameObject::DataRole::Energy].toInt();
    int brightness = 255 - (energyLevel/255)*100;
    QColor color = QColor::fromRgb(brightness, brightness, brightness);
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(color);

    return pixmap;

}

QPixmap ColorRenderer::renderDoorway(const QMap<GameObject::DataRole, const QVariant> &object)
{

}

QPixmap ColorRenderer::renderHealthPack(const QMap<GameObject::DataRole, const QVariant> &object)
{

}

QPixmap ColorRenderer::renderProtagonist(const QMap<GameObject::DataRole, const QVariant> &object)
{

}

QPixmap ColorRenderer::renderEnemy(const QMap<GameObject::DataRole, const QVariant> &object)
{

}

