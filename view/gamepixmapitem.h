#ifndef GAMEPIXMAPITEM_H
#define GAMEPIXMAPITEM_H

#include <QObject>
#include <qgraphicsitem.h>

class GamePixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit GamePixmapItem(const QPixmap &pixmap)
        : QObject()
        , QGraphicsPixmapItem(pixmap) {};

signals:
};

#endif // GAMEPIXMAPITEM_H
