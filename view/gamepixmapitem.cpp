#include "gamepixmapitem.h"

#include <QPropertyAnimation>

int GamePixmapItem::frame() const {
    return m_frame;
}

void GamePixmapItem::setFrame(int newFrame) {
    if(m_frame == newFrame)
        return;
    m_frame = newFrame;
    //    this->setPixmap();
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
    case ObjectType::Enemy:
        animation->setPropertyName("opacity");
        animation->setDuration(3000);
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
