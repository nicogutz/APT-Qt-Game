#ifndef GAMEPIXMAPITEM_H
#define GAMEPIXMAPITEM_H

#include "publicenums.h"
#include <QObject>
#include <qgraphicsitem.h>

class GamePixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged FINAL)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged FINAL)
    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged FINAL)

public:
    explicit GamePixmapItem(const QPixmap &pixmap)
        : QObject()
        , QGraphicsPixmapItem(pixmap) {};

    int frame() const;
    void setFrame(int newFrame);
    void setData(DataRole role, QVariant type);

private:
    int m_frame;
    QImage m_sprite;

signals:
    void posChanged();
    void opacityChanged();
    void frameChanged();
};

#endif // GAMEPIXMAPITEM_H
