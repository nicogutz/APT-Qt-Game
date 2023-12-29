#ifndef GAMEPIXMAPITEM_H
#define GAMEPIXMAPITEM_H

#include <QObject>
#include <qgraphicsitem.h>

class GamePixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged FINAL)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged FINAL)
public:
    explicit GamePixmapItem(const QPixmap &pixmap)
        : QObject()
        , QGraphicsPixmapItem(pixmap) {};

signals:
    void posChanged();
    void opacityChanged();
};

#endif // GAMEPIXMAPITEM_H
