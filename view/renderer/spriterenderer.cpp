#include "spriterenderer.h"
#include "qbitmap.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <iostream>

SpriteRenderer::SpriteRenderer() {
}

GamePixmapItem *SpriteRenderer::renderTile(
  QMap<DataRole, QVariant> object) {
    float energyLevel = object[DataRole::Energy].toFloat() * 100;
    QPixmap pixmap;

    if(energyLevel == INFINITY) {
        pixmap = renderActor(":/images/inf_energy_tile.png", m_cellSize);
    } else if(energyLevel > 60)
        pixmap = renderActor(":/images/high_energy_tile.png", m_cellSize);
    else if(energyLevel > 30)
        pixmap = renderActor(":/images/mid_energy_tile.png", m_cellSize);
    else {
        pixmap = renderActor(":/images/low_energy_tile.png", m_cellSize);
    }
    if(int poisonLevel = object[DataRole::PoisonLevel].toInt()) {
        QPainter painter(&pixmap);
        painter.fillRect(QRect(QPoint(0, 0), pixmap.size()), QColor(0, 255, 0, poisonLevel * 8));
        painter.setCompositionMode(QPainter::CompositionMode_SoftLight);
        painter.drawPixmap(QPoint(0, 0), pixmap);
    }
    return new GamePixmapItem(pixmap);
}

GamePixmapItem *SpriteRenderer::renderDoorway(
  QMap<DataRole, QVariant> object) {
    return new GamePixmapItem(renderActor(":/images/doorway.png", m_cellSize));
}

GamePixmapItem *SpriteRenderer::renderHealthPack(
  QMap<DataRole, QVariant> object) {
    auto pixmap = renderActor(":/images/health_pack.png", m_cellSize);
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

    return new GamePixmapItem(croppedPixmap);
}

GamePixmapItem *SpriteRenderer::renderProtagonist(
  QMap<DataRole, QVariant> object) {
    if(object[DataRole::Health].toInt() == 0) {
        return renderDeath(":/images/protagonist_death.png", 10);
    }
    return new GamePixmapItem(renderActor(":/images/protagonist.png", m_cellSize,
                                          calculateFrame(object[DataRole::Direction].toInt(), 8), 8));
    ;
}

GamePixmapItem *SpriteRenderer::renderEnemy(
  QMap<DataRole, QVariant> object) {
    if(object[DataRole::Health].toInt() == 0) {
        return renderDeath(":/images/xenemy_death.png", 3);
    }
    return new GamePixmapItem(renderActor(":/images/xenemy.png", m_cellSize,
                                          calculateFrame(object[DataRole::Direction].toInt(), 8), 8));
}

GamePixmapItem *SpriteRenderer::renderPEnemy(
  QMap<DataRole, QVariant> object) {
    if(object[DataRole::Health].toInt() == 0) {
        return renderDeath(":/images/penemy_death.png", 5);
    }
    return new GamePixmapItem(renderActor(":/images/penemy.png", m_cellSize,
                                          calculateFrame(object[DataRole::Direction].toInt(), 8), 8));
}

GamePixmapItem *SpriteRenderer::renderMovingEnemy(QMap<DataRole, QVariant> object) {
    if(object[DataRole::Health].toInt() == 0) {
        return renderDeath(":/images/enemy_death.png", 5);
    }
    return new GamePixmapItem(renderActor(":/images/enemy.png", m_cellSize,
                                          calculateFrame(object[DataRole::Direction].toInt(), 8), 8));
}
GamePixmapItem *SpriteRenderer::renderDeath(const QString &imagePath, int numOfFrames) {
    auto *item = new GamePixmapItem(renderActor(imagePath, m_cellSize, 0, numOfFrames));
    item->setCellSize(m_cellSize);
    item->setSprite(QImage(imagePath));
    item->setDeathFrameCount(numOfFrames);
    QPropertyAnimation *deathAnimation = new QPropertyAnimation(item, "frame");
    deathAnimation->setParent(item);
    deathAnimation->setDuration(500 * numOfFrames);
    deathAnimation->setStartValue(0);
    deathAnimation->setEndValue(numOfFrames - 1);
    deathAnimation->setLoopCount(1);
    deathAnimation->start();
    return item;
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
