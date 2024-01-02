#ifndef GAMEPIXMAPITEM_H
#define GAMEPIXMAPITEM_H

#include <QObject>
#include <qgraphicsitem.h>

class GamePixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    Q_PROPERTY(QColor tint READ getTint WRITE setTint NOTIFY tintChanged FINAL)
    //    Q_PROPERTY(QPoint frame READ frame WRITE setFrame NOTIFY frameChanged FINAL)
    //    Q_PROPERTY(QImage sprite READ sprite WRITE setSprite NOTIFY spriteChanged FINAL)
    //    Q_PROPERTY(QSize frameDimension READ frameDimension WRITE setFrameDimension NOTIFY frameDimensionChanged FINAL)

public:
    explicit GamePixmapItem()
        : QObject()
        , QGraphicsPixmapItem() {};

    QPoint frame() const;
    void setFrame(QPoint newFrame);

    QColor getTint() const;
    void setTint(const QColor &newTint);

    void updatePixmap();

    QImage sprite() const;
    void setSprite(QImage newSprite);

    QSize frameDimension() const;
    void setFrameDimension(const QSize &newFrameDimension);

protected:
    inline static constexpr int CELL_SIZE = 50;

private:
    /**
     * @brief m_opacity
     */
    int m_opacity = 255;

    /**
     * @brief m_tint
     */
    QColor m_tint;

    /**
     * @brief m_frameDimension
     */
    QSize m_frameDimension;

    /**
     * @brief m_frame
     */
    QPoint m_frame {0, 0};

    /**
     * @brief m_sprite
     */
    QImage m_sprite;

signals:
    void tintChanged();
    void frameChanged();
    void spriteChanged();
    void frameDimensionChanged();
};

#endif // GAMEPIXMAPITEM_H
