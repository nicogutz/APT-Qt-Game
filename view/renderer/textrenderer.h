#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

/**
 * @brief TextRenderer Performs rendering of the bojects for the text view.
 * Re renders the obje
 */
class TextRenderer : public Renderer {
public:
    /**
     * @brief renderGameObject Makes the ASCII text images from the given data.
     * @param data The GameObject data
     * @param item The Pixmap item
     * Since the changes done by this renderer are difficult to animate, the
     * items that change are re rendered every time.
     */
    void renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) override;

private:
    /**
     * @brief renderTile The only complex rendered text image.
     * @param data The GameObject data
     * @return QImage The tile image
     */
    QImage renderTile(QMap<DataRole, QVariant> data);

    /**
     * @brief renderCharacter Generalized rendering of objects
     * @param str The string representing the object
     * @param color RGB Color to show the image
     * @param direction The direction to rotate the pixmap.
     * @return QImage The image based on the characters in str.
     * Since not all characters are oriented in the same way,
     * some need to rotate relative to the 0 deg of the game.
     */
    QImage renderCharacter(QString str, QColor color, int direction = 0);
};

#endif // TEXTRENDERER_H
