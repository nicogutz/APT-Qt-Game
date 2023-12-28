#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class TextRenderer : public Renderer {
public:
    TextRenderer();

private:
    QPixmap renderTile(QMap<DataRole, QVariant> object) override;
    QPixmap renderDoorway(QMap<DataRole, QVariant> object) override;
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object) override;
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object) override;
    QPixmap renderEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderCharacter(QString, int, int);
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object) override;
    QPixmap renderCharacter(QString str, QColor color);
};

#endif // TEXTRENDERER_H
