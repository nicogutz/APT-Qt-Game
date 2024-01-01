#include "gamepixmapitem.h"
#include "qbitmap.h"
#include "qpainter.h"

#include <QPropertyAnimation>
#include <QRegion>

int GamePixmapItem::frame() const {
    return m_frame;
}

void GamePixmapItem::setFrame(int newFrame) {
    if(m_frame == newFrame)
        return;
    m_frame = newFrame;
    QPixmap framePixmap = renderActor(m_cellSize, m_frame, m_deathFrameCount);
    this->setPixmap(framePixmap);
    emit frameChanged();
}

void GamePixmapItem::setData(DataRole role, QVariant type) {
    auto *animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);
    switch(type.value<ObjectType>()) {
    case ObjectType::Protagonist:
        animation->setPropertyName("pos");
        animation->setDuration(500);
        animation->setLoopCount(-1);
        animation->setStartValue(QPointF(0, 0));
        animation->setEndValue(QPointF(0, 3));
        animation->setEasingCurve(QEasingCurve::OutInBounce);
        animation->start();
        break;
    case ObjectType::MovingEnemy:
        animation->setPropertyName("opacity");
        animation->setDuration(800);
        animation->setLoopCount(-1);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->setEasingCurve(QEasingCurve::SineCurve);
        animation->start();
        break;
    default:
        break;
    }
    return QGraphicsPixmapItem::setData((int)role, type);
}

QImage GamePixmapItem::sprite() const {
    return m_sprite;
}

void GamePixmapItem::setSprite(const QImage &newSprite) {
    m_sprite = newSprite;
}

void GamePixmapItem::setDeathFrameCount(int count) {
    m_deathFrameCount = count;
}

int GamePixmapItem::deathFrameCount() const {
    return m_deathFrameCount;
}

void GamePixmapItem::setCellSize(int cellSize) {
    m_cellSize = cellSize;
}

QColor GamePixmapItem::getTint() const {
    return tint;
}

void GamePixmapItem::setTint(const QColor &newTint) {
    if(tint == newTint)
        return;
    QPixmap currentPixmap = this->pixmap();
    QPixmap overlay(currentPixmap.size());
    overlay.fill(Qt::transparent);
    QPainter painter(&overlay);
    painter.setClipRegion(QRegion(currentPixmap.mask()));
    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    painter.fillRect(overlay.rect(), newTint);
    painter.end();

    auto children = this->childItems();

    QGraphicsPixmapItem *child;
    if(children.empty()) {
        child = new QGraphicsPixmapItem(overlay);
    } else {
        child = dynamic_cast<QGraphicsPixmapItem *>(children[0]);
    }
    child->setParentItem(this);
    child->setPixmap(overlay);
    tint = newTint;
    emit tintChanged();
}

QPixmap GamePixmapItem::renderActor(int cellSize, int POVFrame, int numPOVs) {
    QImage image(m_sprite);

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

// void GamePixmapItem::renderHealthAnimation() {
//     QColor overlayColor = (m_isHealthGain)
//       ? QColor(0, 255, 0, 255 / 2)
//       : QColor(255, 0, 0, 255 / 2);

//    QPixmap currentPixmap = this->pixmap();
//    QPainter painter(&currentPixmap);
//    painter.setClipRegion(QRegion(currentPixmap.mask()));
//    painter.fillRect(currentPixmap.rect(), overlayColor);
//    painter.end();
//    this->setPixmap(currentPixmap);
//}
