#ifndef GAMEPIXMAPITEM_H
#define GAMEPIXMAPITEM_H

#include <QObject>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QPointer>
#include <qgraphicsitem.h>

class GamePixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    Q_PROPERTY(QColor tint READ getTint WRITE setTint NOTIFY tintChanged FINAL)
    Q_PROPERTY(QPoint frame READ frame WRITE setFrame NOTIFY frameChanged FINAL)
    Q_PROPERTY(QPointF scaling READ scaling WRITE setScaling NOTIFY scalingChanged FINAL)

public:
    explicit GamePixmapItem()
        : QObject()
        , QGraphicsPixmapItem() {
        m_animationGroup = new QParallelAnimationGroup;
        m_animationGroup->setParent(this);
        m_animationGroup->insertAnimation(0, new QSequentialAnimationGroup);
    };

    QPoint frame() const;
    void setFrame(QPoint newFrame);

    QColor getTint() const;
    void setTint(const QColor &newTint);
    void setTint(const QColor &newTint, bool onParent);

    QImage sprite() const;
    void setSprite(QImage newSprite);

    QSize frameDimension() const;
    void setFrameDimension(const QSize &newFrameDimension);

    void updatePixmap();
    void updateOverlay();

    void addAnimation(QPropertyAnimation *animation, bool sequential = false);

    const QPointer<QParallelAnimationGroup> animationGroup() const;

    QPointF scaling() const;
    void setScaling(QPointF newScaling);

protected:
    inline static constexpr int CELL_SIZE = 50;

private:
    /**
     * @brief m_opacity Opacity of the base QPixmap.
     */
    int m_opacity = 255;

    /**
     * @brief m_tint The tint of the overlay.
     */
    QColor m_tint;

    /**
     * @brief m_frameDimension The size of a single frame.
     */
    QSize m_frameDimension;

    /**
     * @brief m_frame The selected frame, sprites can have more than one row.
     */
    QPoint m_frame {0, 0};

    /**
     * @brief m_sprite
     */
    QImage m_sprite;

    /**
     * @brief m_position
     */
    QPointF m_scaling {1, 1};

    /**
     * @brief m_animationGroup
     */
    QPointer<QParallelAnimationGroup> m_animationGroup;

signals:
    void tintChanged();
    void frameChanged();
    void spriteChanged();
    void frameDimensionChanged();
    void scalingChanged();
};

#endif // GAMEPIXMAPITEM_H
