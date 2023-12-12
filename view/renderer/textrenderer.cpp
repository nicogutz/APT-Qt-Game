#include "textrenderer.h"
#include "qpainter.h"
#include "qpixmap.h"
#include <QFont>


TextRenderer::TextRenderer() {
}

QPixmap TextRenderer::renderTile(QMap<GameObject::DataRole, QVariant> object) {
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black));
    painter.drawRect(0, 0, cellSize - 1, cellSize - 1);
    return pixmap;
}

QPixmap TextRenderer::renderDoorway(QMap<GameObject::DataRole, QVariant> object ) {
    return renderCharacter('D', 100, 100);  // No special conditions for Doorway
}

QPixmap TextRenderer::renderHealthPack(QMap<GameObject::DataRole, QVariant> object) {
    int healthLevel = object[GameObject::DataRole::Health].toInt();
    return renderCharacter('H', 100, healthLevel);
}

QPixmap TextRenderer::renderProtagonist(QMap<GameObject::DataRole, QVariant> object) {
    int healthLevel = object[GameObject::DataRole::Health].toInt();
    int energyLevel = object[GameObject::DataRole::Energy].toInt();
    return renderCharacter('P',  energyLevel, healthLevel);
}

QPixmap TextRenderer::renderEnemy(QMap<GameObject::DataRole, QVariant> object) {
    int healthLevel = object[GameObject::DataRole::Health].toInt();
    int poisonLevel = object[GameObject::DataRole::PoisonLevel].toInt();
    return renderCharacter('E', poisonLevel, healthLevel);
}

QPixmap TextRenderer::renderCharacter(char character, int weight, int size=100) {
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = painter.font();
    font.setBold(weight > 50);  // If weight is above 50, make the font bold
    font.setPointSize((cellSize / 2 - 10) + (size/10) );  // Set the font size relative to cell size
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setWidth(weight / 10);  // Adjust pen width based on weight
    painter.setPen(pen);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(character));
    return pixmap;
}
