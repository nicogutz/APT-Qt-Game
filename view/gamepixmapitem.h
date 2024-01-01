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

    QImage sprite() const;
    void setSprite(const QImage &newSprite);

    void setDeathFrameCount(int count);

    int deathFrameCount() const;

    void setCellSize(int cellSize);

    QColor getTint() const;
    void setTint(const QColor &newTint);

private:
    int m_frame, m_deathFrameCount, m_cellSize;
    QColor tint;
    QImage m_sprite;
    QPixmap renderActor(int cellSize, int POVFrame, int numPOVs);

    Q_PROPERTY(QColor tint READ getTint WRITE setTint NOTIFY tintChanged FINAL)

signals:
    void posChanged();
    void opacityChanged();
    void frameChanged();
    void tintChanged();
};

#endif // GAMEPIXMAPITEM_H
