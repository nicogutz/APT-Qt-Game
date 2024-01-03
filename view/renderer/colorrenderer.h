#ifndef COLORRENDERER_H
#define COLORRENDERER_H

#include "renderer.h"
#include <algorithm>
#include <QBrush>
#include <QPainter>
#include <iostream>
#include <QtGlobal>

class ColorRenderer : public Renderer {
public:
    ColorRenderer() { }
    void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) override;

private:
    QPixmap renderTile(QMap<DataRole, QVariant> object);
    QPixmap renderDoorway(QMap<DataRole, QVariant> object);
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object);
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object);
    QPixmap renderEnemy(QMap<DataRole, QVariant> object);
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object);
    QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object);
};

#endif // COLORRENDERER_H
