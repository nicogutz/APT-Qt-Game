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
    ColorRenderer();
    void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) override;

private:
    QPixmap renderTile(QMap<DataRole, QVariant> object) override;
    QPixmap renderDoorway(QMap<DataRole, QVariant> object) override;
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object) override;
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object) override;
    QPixmap renderEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object) override;
};

#endif // COLORRENDERER_H
