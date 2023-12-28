#include "spriterenderer.h"
#include <QPainter>
#include <iostream>

SpriteRenderer::SpriteRenderer() {
}

QPixmap SpriteRenderer::renderTile(
  QMap<DataRole, QVariant> object) {
    float energyLevel = object[DataRole::Energy].toFloat() * 100;
    if (energyLevel > 60)
        return renderActor(":/images/high_energy_tile.png", cellSize);
    else if (energyLevel > 30)
        return renderActor(":/images/mid_energy_tile.png", cellSize);
    return renderActor(":/images/low_energy_tile.png", cellSize);
}

QPixmap SpriteRenderer::renderDoorway(
  QMap<DataRole, QVariant> object) {
    return renderActor(":/images/doorway.png", cellSize);

}

QPixmap SpriteRenderer::renderHealthPack(
  QMap<DataRole, QVariant> object) {
    return renderActor(":/images/health_pack.png", cellSize);

}

QPixmap SpriteRenderer::renderProtagonist(
  QMap<DataRole, QVariant> object) {
    return renderActor(":/images/protagonist.png", cellSize, calculateFrame(object[DataRole::Direction].toInt(), 8), 8);
}

QPixmap SpriteRenderer::renderEnemy(
  QMap<DataRole, QVariant> object) {
    return renderActor(":/images/penemy.png", cellSize, calculateFrame(object[DataRole::Direction].toInt(), 8), 8);
}

QPixmap SpriteRenderer::renderPEnemy(
    QMap<DataRole, QVariant> object) {
    return renderActor(":/images/penemy.png", cellSize, calculateFrame(object[DataRole::Direction].toInt(), 8), 8);
}


QPixmap SpriteRenderer::renderActor(const QString& imagePath, int cellSize) {

    QPixmap resultPixmap(cellSize, cellSize);
    resultPixmap.fill(Qt::transparent);

    QPainter painter(&resultPixmap);
    painter.drawImage(resultPixmap.rect(), QImage(imagePath));
    painter.end();

    return resultPixmap;
}

QPixmap SpriteRenderer::renderActor(const QString& imagePath, int cellSize, int POVFrame, int numPOVs) {

    QImage image(imagePath);

    int frameWidth = image.width() / numPOVs;
    QRect frameRect(POVFrame * frameWidth, 0, frameWidth, image.height());
    QImage POVImage = image.copy(frameRect);


    QPixmap resultPixmap(cellSize, cellSize);
    resultPixmap.fill(Qt::transparent);

    QPainter painter(&resultPixmap);
    QRect targetRect(5, 5, cellSize - 10, cellSize - 10);

    painter.drawImage(targetRect, POVImage);
    painter.end();

    return resultPixmap;
}

int SpriteRenderer::calculateFrame(int direction, int numPOVs) {
    return ((direction / 45 + 2) % numPOVs);
}



















