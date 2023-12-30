#include <QFont>
#include <QPainter>
#include <QPen>
#include <QRandomGenerator>
#include "textrenderer.h"

TextRenderer::TextRenderer() {
}

GamePixmapItem *TextRenderer::renderTile(QMap<DataRole, QVariant> object) {
    // The Pixmaps have to be transparent, text is AAd by default
    QPixmap pixmap(m_cellSize, m_cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QFont font = painter.font();
    font.setBold(true);
    font.setKerning(false);
    font.setFixedPitch(true);
    font.setPointSize(m_cellSize / 4); // Set the font size relative to cell size
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    font.setWeight(QFont::Black);
    painter.setFont(font);
    painter.setLayoutDirection(Qt::LeftToRight);

    // This has to be calculated to know the offset of the underscore characters
    QFontMetrics fontMetrics(font);
    int linePosition = ((m_cellSize - fontMetrics.horizontalAdvance("_")) / 4);

    // Draw the bottom lines, we don't need top lines unless we are at the top
    // The offsets are a bit arbitrary on the y ax.
    painter.drawText(linePosition - 4, m_cellSize - 3, "_");
    painter.drawText(2 * linePosition - 4, m_cellSize - 3, "_");
    painter.drawText(3 * linePosition - 4, m_cellSize - 3, "_");
    painter.drawText(4 * linePosition - 4, m_cellSize - 3, "_");

    if(!object[DataRole::Position].toPoint().y()) {
        painter.drawText(linePosition - 4, 0, "_");
        painter.drawText(2 * linePosition - 4, 0, "_");
        painter.drawText(3 * linePosition - 4, 0, "_");
        painter.drawText(4 * linePosition - 4, 0, "_");
    }

    // The | characters are much longer than the _ so we make them smaller
    font.setPointSize(m_cellSize / 8);
    font.setStretch(125);
    painter.setFont(font);

    // This looks extremely funky but it is what it is
    painter.drawText(-1, m_cellSize / 4 - 2, "|");
    painter.drawText(-1, 2 * (m_cellSize / 4) - 2, "|");
    painter.drawText(-1, 3 * (m_cellSize / 4) - 2, "|");
    painter.drawText(-1, m_cellSize - 2, "|");
    // Since the renderer has no idea about the size of the world,
    // It cannot simply know where the
    painter.drawText(m_cellSize - 2, m_cellSize / 4 - 2, "|");
    painter.drawText(m_cellSize - 2, 2 * (m_cellSize / 4) - 2, "|");
    painter.drawText(m_cellSize - 2, 3 * (m_cellSize / 4) - 2, "|");
    painter.drawText(m_cellSize - 2, m_cellSize - 2, "|");

    if(int poisonLevel = object[DataRole::PoisonLevel].toInt()) {
        painter.setBrush(QBrush(Qt::green));
        int maxDots = m_cellSize;
        int numberOfDots = (maxDots * poisonLevel);
        for(int i = 0; i < numberOfDots; ++i) {
            int randomX = QRandomGenerator::global()->bounded(m_cellSize);
            int randomY = QRandomGenerator::global()->bounded(m_cellSize);
            painter.drawText(randomX, randomY, ".");
        }
    }
    return new GamePixmapItem(pixmap);
}

GamePixmapItem *TextRenderer::renderDoorway(QMap<DataRole, QVariant>) {
    return new GamePixmapItem(renderCharacter("|_|", 100, 100)); // No special conditions for Doorway
}

GamePixmapItem *TextRenderer::renderHealthPack(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    QColor color("blue");
    color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());
    return new GamePixmapItem(renderCharacter("c[_]", color));
}

GamePixmapItem *TextRenderer::renderProtagonist(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int direction = object[DataRole::Direction].toInt();
    QColor color("black");
    color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());

    return new GamePixmapItem(rotatePixmap(renderCharacter("ʕʘ̅͜ʘ̅ʔ", color), direction));
}

GamePixmapItem *TextRenderer::renderEnemy(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int direction = object[DataRole::Direction].toInt();

    QColor color("red");
    color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());

    return new GamePixmapItem(rotatePixmap(renderCharacter("⊙_◎", color), direction));
}

GamePixmapItem *TextRenderer::renderPEnemy(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int poisonLevel = object[DataRole::PoisonLevel].toInt();
    int direction = object[DataRole::Direction].toInt();
    QColor color;
    if(healthLevel <= 0) {
        color = QColor("darkgreen");
        color.setHsv(color.hue(), poisonLevel, color.value(), color.alpha());

    } else {
        color = QColor("green");
        color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());
    }

    return new GamePixmapItem(rotatePixmap(renderCharacter("ⓧⓧ", color), direction));
}

QPixmap TextRenderer::renderCharacter(QString str, QColor color) {
    QPixmap pixmap(m_cellSize, m_cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QFont font = painter.font();
    font.setBold(true);
    font.setKerning(false);
    font.setFixedPitch(true);
    font.setPointSize(m_cellSize / 4); // Set the font size relative to cell size
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    font.setWeight(QFont::Black);
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setColor(color);
    painter.setPen(pen);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(str));
    painter.end();

    return pixmap;
}

QPixmap TextRenderer::renderCharacter(QString str, int weight, int size = 100) {
    QPixmap pixmap(m_cellSize, m_cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = painter.font();
    font.setBold(weight > 50);
    font.setPointSize((m_cellSize / 2 - 20) + (size / 20));
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setWidth(weight / 10);
    painter.setPen(pen);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(str));
    painter.end();

    return pixmap;
}
