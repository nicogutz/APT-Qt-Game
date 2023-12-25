#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {
public:
    TextRenderer();
    QPixmap renderTile(QMap<DataRole, QVariant> object) override;
    QPixmap renderDoorway(QMap<DataRole, QVariant> object) override;
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object) override;
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object) override;
    QPixmap renderEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderCharacter(QString, int, int);
};

#endif // TEXTRENDERER_H
