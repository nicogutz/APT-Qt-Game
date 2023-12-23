#include "renderer.h"

Renderer::Renderer() {
}

QGraphicsPixmapItem *Renderer::renderGameObjects(QList<QMap<DataRole, QVariant>> objectDataList) {
    QGraphicsPixmapItem *tile;
    tile = new QGraphicsPixmapItem(renderTile(objectDataList[0]));
    QGraphicsPixmapItem *item;

    for(auto data : objectDataList.mid(1, -1)) {
        switch(data[DataRole::Type].toInt()) {
        case static_cast<int>(ObjectType::Tile):
            item = new QGraphicsPixmapItem(renderTile(data));
            item->setParentItem(tile);
            break;
        case static_cast<int>(ObjectType::Doorway):
            item = new QGraphicsPixmapItem(renderDoorway(data));
            item->setParentItem(tile);
            break;
        case static_cast<int>(ObjectType::HealthPack):
            item = new QGraphicsPixmapItem(renderHealthPack(data));
            item->setParentItem(tile);
            break;
        case static_cast<int>(ObjectType::Protagonist):
            item = new QGraphicsPixmapItem(renderProtagonist(data));
            item->setParentItem(tile);
            break;
        default:
            // Handle default case or unknown types
            item = new QGraphicsPixmapItem(renderEnemy(data));
            item->setParentItem(tile);
            break;
        }
    }

    return tile;
}

QGraphicsPixmapItem *Renderer::renderGameObject(QMap<DataRole, QVariant> objectData) {
    QGraphicsPixmapItem *tile;
    tile = new QGraphicsPixmapItem(renderTile(objectData));
    QGraphicsPixmapItem *item;

    switch(objectData[DataRole::Type].toInt()) {
    case static_cast<int>(ObjectType::Tile):
        item = new QGraphicsPixmapItem(renderTile(objectData));
        item->setParentItem(tile);
        break;
    case static_cast<int>(ObjectType::Doorway):
        item = new QGraphicsPixmapItem(renderDoorway(objectData));
        item->setParentItem(tile);
        break;
    case static_cast<int>(ObjectType::HealthPack):
        item = new QGraphicsPixmapItem(renderHealthPack(objectData));
        item->setParentItem(tile);
        break;
    case static_cast<int>(ObjectType::Protagonist):
        item = new QGraphicsPixmapItem(renderProtagonist(objectData));
        item->setParentItem(tile);
        break;
    default:
        // Handle default case or unknown types
        item = new QGraphicsPixmapItem(renderEnemy(objectData));
        item->setParentItem(tile);
        break;
    }

    return tile;
}

QPixmap Renderer::rotatePixmap(const QPixmap &originalPixmap, int direction) {
    QTransform transformation;
    transformation.rotate(direction);

    return originalPixmap.transformed(transformation);
}
