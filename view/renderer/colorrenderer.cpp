#include "colorrenderer.h"
#include "qpixmap.h"

ColorRenderer::ColorRenderer() {
}
int cellSize = 50;

QPixmap ColorRenderer::renderTile(
    QMap<GameObject::DataRole, QVariant> object) {
    int energyLevel = object[GameObject::DataRole::Energy].toInt();
    int brightness = 255 - (energyLevel / 255) * 100;
    QColor color
        = QColor::fromRgb(brightness, brightness, brightness);
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(color);

    return pixmap;
}

QPixmap ColorRenderer::renderDoorway(
    QMap<GameObject::DataRole, QVariant> object) {
}

QPixmap ColorRenderer::renderHealthPack(
    QMap<GameObject::DataRole, QVariant> object) {
}

QPixmap ColorRenderer::renderProtagonist(
    QMap<GameObject::DataRole, QVariant> object) {
}

QPixmap ColorRenderer::renderEnemy(
    QMap<GameObject::DataRole, QVariant> object) {
}

