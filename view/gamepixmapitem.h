#ifndef GAMEPIXMAPITEM_H
#define GAMEPIXMAPITEM_H

#include "publicenums.h"
#include <QObject>
#include <qgraphicsitem.h>

class GamePixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    //    Q_PROPERTY(QPoint frame READ frame WRITE setFrame NOTIFY frameChanged FINAL)
    Q_PROPERTY(QColor tint READ getTint WRITE setTint NOTIFY tintChanged FINAL)
    //    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged FINAL)

public:
    explicit GamePixmapItem()
        : QObject()
        , QGraphicsPixmapItem() {};

    QColor getTint() const;
    void setTint(const QColor &newTint);

private:
    QPixmap renderFrame();

    QPoint m_frame;
    QColor m_tint;
    QImage m_sprite;

signals:
    void posChanged();
    void opacityChanged();
    void frameChanged();
    void tintChanged();
};

#endif // GAMEPIXMAPITEM_H
