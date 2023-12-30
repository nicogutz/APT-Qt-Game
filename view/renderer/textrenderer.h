#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {
public:
    TextRenderer();

private:
    GamePixmapItem *renderTile(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderDoorway(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderHealthPack(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderProtagonist(QMap<DataRole, QVariant> object) override;
    GamePixmapItem *renderEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderCharacter(QString, int, int);
    GamePixmapItem *renderPEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderCharacter(QString str, QColor color);
    GamePixmapItem *renderMovingEnemy(QMap<DataRole, QVariant> object) override;
};

#endif // TEXTRENDERER_H
