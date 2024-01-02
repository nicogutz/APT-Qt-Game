#include "spriterenderer.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <iostream>

void SpriteRenderer::renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) {
    //    if(!item->isActive()) {
    Renderer::renderGameObject(objectData, item);
    //    }
}

QPixmap SpriteRenderer::renderTile(
  QMap<DataRole, QVariant> object) {
    float energyLevel = round(object[DataRole::Energy].toFloat() * 19);
    int tileSelected = energyLevel == INFINITY ? 20 : energyLevel;

    QRect rect(tileSelected * TILE_SIZE, 0, 32, 32);
    return QPixmap::fromImage(m_tiles.copy(rect)).scaled(CELL_SIZE, CELL_SIZE);
}

QPixmap SpriteRenderer::renderDoorway(QMap<DataRole, QVariant> object) {
    return rotatePixmap(renderActor(":/images/doorway.png", CELL_SIZE), object[DataRole::Direction].toInt());
}

QPixmap SpriteRenderer::renderHealthPack(
  QMap<DataRole, QVariant> object) {
    auto pixmap = renderActor(":/images/health_pack.png", CELL_SIZE);
    int health = object[DataRole::Health].toInt();

    QPainterPath piePath;
    piePath.moveTo(pixmap.rect().center());
    piePath.arcTo(pixmap.rect(), 0, health * 10);

    QPixmap croppedPixmap(pixmap.size());
    croppedPixmap.fill(Qt::transparent);

    QPainter painter(&croppedPixmap);
    painter.setClipPath(piePath);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();

    return croppedPixmap;
}

QPixmap SpriteRenderer::renderProtagonist(
  QMap<DataRole, QVariant> object) {
    return renderActor(":/images/protagonist.png", CELL_SIZE, calculateFrame(object[DataRole::Direction].toInt(), 8), 8);
}

QPixmap SpriteRenderer::renderEnemy(
  QMap<DataRole, QVariant> object) {
    return renderActor(":/images/xenemy.png", CELL_SIZE, calculateFrame(object[DataRole::Direction].toInt(), 8), 8);
}

QPixmap SpriteRenderer::renderPEnemy(
  QMap<DataRole, QVariant> object) {
    return renderActor(":/images/penemy.png", CELL_SIZE, calculateFrame(object[DataRole::Direction].toInt(), 8), 8);
}

QPixmap SpriteRenderer::renderMovingEnemy(QMap<DataRole, QVariant> object) {
    return renderActor(":/images/enemy.png", CELL_SIZE, calculateFrame(object[DataRole::Direction].toInt(), 8), 8);
}

QPixmap SpriteRenderer::renderActor(const QString &imagePath, int cellSize) {
    QPixmap resultPixmap(cellSize, cellSize);
    resultPixmap.fill(Qt::transparent);

    QPainter painter(&resultPixmap);
    painter.drawImage(resultPixmap.rect(), QImage(imagePath));
    painter.end();
    return resultPixmap;
}

QPixmap SpriteRenderer::renderActor(const QString &imagePath, int cellSize, int POVFrame, int numPOVs) {
    QImage image(imagePath);

    int frameWidth = image.width() / numPOVs;
    QRect frameRect(POVFrame * frameWidth, 0, frameWidth, image.height());
    QImage POVImage = image.copy(frameRect);

    QPixmap resultPixmap(cellSize, cellSize);
    resultPixmap.fill(Qt::transparent);

    QPainter painter(&resultPixmap);
    QRect targetRect(cellSize / 10, cellSize / 10, cellSize - (cellSize * 2 / 10), cellSize - (cellSize * 2 / 10));

    painter.drawImage(targetRect, POVImage);
    painter.end();

    return resultPixmap;
}

int SpriteRenderer::calculateFrame(int direction, int numPOVs) {
    return ((direction / 45 + 2) % numPOVs);
}
