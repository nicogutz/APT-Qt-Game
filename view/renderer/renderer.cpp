#include "renderer.h"

Renderer::Renderer() {
}

QGraphicsPixmapItem *
Renderer::renderGameObject(const QVector<QMap<GameObject::DataRole, QVariant>> &dt_ls) {
    QGraphicsPixmapItem *tile;
    tile = new QGraphicsPixmapItem(renderTile(dt_ls[0]));
    QGraphicsPixmapItem *item;

    for(auto data : dt_ls.mid(1, -1)) {
        switch(data[GameObject::DataRole::Type].toInt()) {
        case static_cast<int>(GameObject::ObjectType::Tile):
            item = new QGraphicsPixmapItem(renderTile(data));
            item->setParentItem(tile);
            break;
        case static_cast<int>(GameObject::ObjectType::Doorway):
            item = new QGraphicsPixmapItem(renderDoorway(data));
            item->setParentItem(tile);
            break;
        case static_cast<int>(GameObject::ObjectType::HealthPack):
            item = new QGraphicsPixmapItem(renderHealthPack(data));
            item->setParentItem(tile);
            break;
        case static_cast<int>(GameObject::ObjectType::Protagonist):
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

QPixmap Renderer::rotatePixmap(const QPixmap &originalPixmap, int direction) {

    QTransform transformation;
    transformation.rotate(direction);

    return originalPixmap.transformed(transformation);
}

