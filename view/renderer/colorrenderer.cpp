#include "colorrenderer.h"
#include "qpainter.h"
#include "qpixmap.h"

int cellSize = 50;
ColorRenderer::ColorRenderer() {
}

QPixmap ColorRenderer::renderTile(
    QMap<GameObject::DataRole, QVariant> object) {
    int energyLevel = object[GameObject::DataRole::Energy].toInt();
    int brightness = 255 - (energyLevel * 255 / 100);
    QColor color(brightness, brightness, brightness);

    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(color);

    return pixmap;
}

QPixmap ColorRenderer::renderDoorway(
    QMap<GameObject::DataRole, QVariant> object) {

    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent);

    QColor color(123, 63, 0);


    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing); // For smoother edges

    // Set the pen for the border and brush for the fill
    QPen pen(Qt::transparent);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(QBrush(color));

    // Define points for the rhombus
    QPoint topleft(cellSize / 5, cellSize / 5);
    QPoint topright(cellSize - (cellSize/5),  cellSize / 5);
    QPoint bottomleft(cellSize / 5, cellSize - (cellSize / 5));
    QPoint bootomright(cellSize - (cellSize / 5), cellSize - (cellSize / 5));

    QVector<QPoint> points = {topleft, topright, bottomleft, bootomright};

    // Draw the rhombus
    painter.drawPolygon(points.data(), points.size());

    painter.end();

    return pixmap;
}


QPixmap ColorRenderer::renderHealthPack(
    QMap<GameObject::DataRole, QVariant> object) {

    int healthLevel = object[GameObject::DataRole::Health].toInt();
    int minIntensity = 50;
    int maxIntensity = 255;
    int final_color = minIntensity + (maxIntensity - minIntensity) * healthLevel / 100;
    QColor color(0, final_color, 0);

    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent); // Fill the pixmap with a transparent background

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing); // For smoother edges

    // Set the pen for the border and brush for the fill
    QPen pen(Qt::transparent);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(QBrush(color));

    // Define points for the rhombus
    QPoint top(cellSize / 2, cellSize / 5);
    QPoint right(cellSize - (cellSize/5),  cellSize / 2);
    QPoint bottom(cellSize / 2, cellSize - (cellSize / 5));
    QPoint left(cellSize / 5, cellSize / 2);

    QVector<QPoint> points = {top, right, bottom, left};

    // Draw the rhombus
    painter.drawPolygon(points.data(), points.size());

    painter.end();

    return pixmap;
}

QPixmap ColorRenderer::renderProtagonist(
    QMap<GameObject::DataRole, QVariant> object) {

    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent); // Transparent background

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define the star points
    QVector<QPoint> starPoints = {
        QPoint(cellSize / 2, cellSize / 5),
        QPoint(cellSize * 3 / 5, cellSize * 3 / 5),
        QPoint(cellSize, cellSize * 2 / 5),
        QPoint(cellSize * 2 / 5, cellSize * 2 / 5),
        QPoint(cellSize / 2, cellSize),
        QPoint(cellSize / 2, cellSize / 5),
        QPoint(cellSize * 3 / 5, cellSize * 2 / 5),
        QPoint(cellSize / 5, cellSize * 2 / 5),
        QPoint(cellSize * 2 / 5, cellSize * 3 / 5),
        QPoint(cellSize / 2, cellSize / 5)
    };

    QPolygon leftHalf(starPoints.mid(0, 6)); // Left half of the star
    QPolygon rightHalf(starPoints.mid(5)); // Right half of the star

    // Draw and fill left half with health - green
    int healthLevel = object[GameObject::DataRole::Health].toInt();
    int minIntensity = 50;
    int maxIntensity = 255;
    int final_color = minIntensity + (maxIntensity - minIntensity) * healthLevel / 100;
    QColor color(0, final_color, 0);
    painter.setBrush(QBrush(color));
    painter.drawPolygon(leftHalf);

    // Draw and fill right half with energy - yellow
    int energyLevel = object[GameObject::DataRole::Energy].toInt();
    minIntensity = 50;
    maxIntensity = 255;
    final_color = minIntensity + (maxIntensity - minIntensity) * energyLevel / 100;
    QColor energyColor(final_color, final_color, 0);
    painter.setBrush(QBrush(energyColor));
    painter.drawPolygon(rightHalf);

    painter.end();

    return pixmap;
}

QPixmap ColorRenderer::renderEnemy(
    QMap<GameObject::DataRole, QVariant> object) {
}

