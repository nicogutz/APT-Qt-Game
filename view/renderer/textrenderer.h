#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

/**
 * @brief The TextRenderer class
 */
class TextRenderer : public Renderer {
public:
    /**
     * @brief TextRenderer
     * Performs rendering of the bojects for the text view
     */
    TextRenderer();

    /**
     * @brief renderGameObject performs the selection of the function used to render based on the ObjectType
     * @param objectData
     * @param item
     */
    void renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) override;

private:
    /**
     * @brief renderTile renders tile object
     * @param object
     * @return QPixmap
     */
    QImage renderTile(QMap<DataRole, QVariant> data);

    /**
     * @brief renderCharacter generalized rendering of objects
     * @param str
     * @param color
     * @return QPixmap
     */
    QImage renderCharacter(QString str, QColor color, int direction = 0);
};

#endif // TEXTRENDERER_H
