#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {
public:
    TextRenderer();
    void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) override;

private:
    QPixmap renderTile(QMap<DataRole, QVariant> object) override;
    QPixmap renderDoorway(QMap<DataRole, QVariant> object) override;
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object) override;
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object) override;
    QPixmap renderEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object) override;

    QPixmap renderCharacter(QString str, QColor color);
    QPixmap renderCharacter(QString str, int weight, int size = 100);
};

#endif // TEXTRENDERER_H
