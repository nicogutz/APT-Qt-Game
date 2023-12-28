#include <QFont>
#include <QPainter>
#include <QPen>
#include "textrenderer.h"

TextRenderer::TextRenderer() {
}

QPixmap TextRenderer::renderTile(QMap<DataRole, QVariant> object) {
    // The Pixmaps have to be transparent, text is AAd by default
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QFont font = painter.font();
    font.setBold(true);
    font.setKerning(false);
    font.setFixedPitch(true);
    font.setPointSize(cellSize / 4); // Set the font size relative to cell size
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    font.setWeight(QFont::Black);
    painter.setFont(font);
    painter.setLayoutDirection(Qt::LeftToRight);

    // This has to be calculated to know the offset of the underscore characters
    QFontMetrics fontMetrics(font);
    int linePosition = ((cellSize - fontMetrics.horizontalAdvance("_")) / 4);

    // Draw the bottom lines, we don't need top lines unless we are at the top
    // The offsets are a bit arbitrary on the y ax.
    painter.drawText(linePosition - 4, cellSize - 3, "_");
    painter.drawText(2 * linePosition - 4, cellSize - 3, "_");
    painter.drawText(3 * linePosition - 4, cellSize - 3, "_");
    painter.drawText(4 * linePosition - 4, cellSize - 3, "_");

    if(!object[DataRole::Position].toPoint().y()) {
        painter.drawText(linePosition - 4, 0, "_");
        painter.drawText(2 * linePosition - 4, 0, "_");
        painter.drawText(3 * linePosition - 4, 0, "_");
        painter.drawText(4 * linePosition - 4, 0, "_");
    }

    // The | characters are much longer than the _ so we make them smaller
    font.setPointSize(cellSize / 8);
    font.setStretch(125);
    painter.setFont(font);

    // This looks extremely funky but it is what it is
    painter.drawText(-1, cellSize / 4 - 2, "|");
    painter.drawText(-1, 2 * (cellSize / 4) - 2, "|");
    painter.drawText(-1, 3 * (cellSize / 4) - 2, "|");
    painter.drawText(-1, cellSize - 2, "|");
    // Since the renderer has no idea about the size of the world,
    // It cannot simply know where the
    painter.drawText(cellSize - 2, cellSize / 4 - 2, "|");
    painter.drawText(cellSize - 2, 2 * (cellSize / 4) - 2, "|");
    painter.drawText(cellSize - 2, 3 * (cellSize / 4) - 2, "|");
    painter.drawText(cellSize - 2, cellSize - 2, "|");

    return pixmap;
}

QPixmap TextRenderer::renderDoorway(QMap<DataRole, QVariant> object) {
    return renderCharacter("|_|", 100, 100); // No special conditions for Doorway
}

QPixmap TextRenderer::renderHealthPack(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    return renderCharacter("c[_]", 100, healthLevel);
}

QPixmap TextRenderer::renderProtagonist(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int energyLevel = object[DataRole::Energy].toInt();
    int direction = object[DataRole::Direction].toInt();

    QPixmap pixmap = rotatePixmap(renderCharacter("ʕ·͡ᴥ·ʔ", energyLevel, healthLevel), direction);
    return pixmap;
}

QPixmap TextRenderer::renderEnemy(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int poisonLevel = object[DataRole::PoisonLevel].toInt();
    int direction = object[DataRole::Direction].toInt();
    QPixmap pixmap = rotatePixmap(renderCharacter("[º.°]", poisonLevel, healthLevel), direction);
    return pixmap;
}

QPixmap TextRenderer::renderPEnemy(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int poisonLevel = object[DataRole::PoisonLevel].toInt();
    int direction = object[DataRole::Direction].toInt();
    QPixmap pixmap = rotatePixmap(renderCharacter("[OO]", poisonLevel, healthLevel), direction);
    return pixmap;
}

QPixmap TextRenderer::renderCharacter(QString str, int weight, int size = 100) {
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = painter.font();
    font.setBold(weight > 50); // If weight is above 50, make the font bold
    font.setPointSize((cellSize / 2 - 20) + (size / 20)); // Set the font size relative to cell size
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setWidth(weight / 10); // Adjust pen width based on weight
    painter.setPen(pen);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(str));
    painter.end();

    return pixmap;
}
