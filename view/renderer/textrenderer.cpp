#include <QFont>
#include <QPainter>
#include <QPen>
#include "textrenderer.h"

TextRenderer::TextRenderer() {
}

QPixmap TextRenderer::renderTile(QMap<DataRole, QVariant> object) {
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen = painter.pen();
    pen.setWidth(5);
    painter.setPen(pen);

    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(cellSize/2); // Set the font size relative to cell size
    painter.setFont(font);

    painter.drawText(pixmap.rect().adjusted(0, -35, 0, 0), Qt::AlignTop | Qt::AlignHCenter, QString("_"));
    painter.drawText(pixmap.rect().adjusted(0, 5, 0, 0), Qt::AlignBottom | Qt::AlignHCenter, QString("_"));
    painter.drawText(pixmap.rect().adjusted(0, -10, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, QString("|"));
    painter.drawText(pixmap.rect().adjusted(0, -10, 0, 0), Qt::AlignRight | Qt::AlignVCenter, QString("|"));


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

