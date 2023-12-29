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

private:
    GamePixmapItem *renderTile(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderDoorway(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderHealthPack(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderProtagonist(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderEnemy(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderPEnemy(QMap<DataRole, QVariant> object) override;
};

#endif // COLORRENDERER_H
