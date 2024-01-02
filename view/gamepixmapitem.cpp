#include "gamepixmapitem.h"
#include "qbitmap.h"
#include "qpainter.h"

#include <QPropertyAnimation>
#include <QRegion>

// int GamePixmapItem::frame() const {
//     return m_frame;
// }

// void GamePixmapItem::setFrame(int newFrame) {
//     if(m_frame == newFrame)
//         return;
//     m_frame = newFrame;
////    QPixmap framePixmap = renderActor(m_cellSize, m_frame, m_deathFrameCount);
//    this->setPixmap(framePixmap);
//    emit frameChanged();
//}

QColor GamePixmapItem::getTint() const {
    return m_tint;
}

void GamePixmapItem::setTint(const QColor &newTint) {
    if(m_tint == newTint)
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
    m_tint = newTint;
    emit tintChanged();
}

// QPixmap GamePixmapItem::renderActor(int cellSize, int POVFrame, int numPOVs) {
//     QImage image(m_sprite);

//    int frameWidth = image.width() / numPOVs;
//    QRect frameRect(POVFrame * frameWidth, 0, frameWidth, image.height());
//    QImage POVImage = image.copy(frameRect);

//    QPixmap resultPixmap(cellSize, cellSize);
//    resultPixmap.fill(Qt::transparent);

//    QPainter painter(&resultPixmap);
//    QRect targetRect(cellSize / 10, cellSize / 10, cellSize - (cellSize * 2 / 10), cellSize - (cellSize * 2 / 10));

//    painter.drawImage(targetRect, POVImage);
//    painter.end();

//    return resultPixmap;
//}
