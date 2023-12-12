#include "renderer.h"

Renderer::Renderer() {
}

QGraphicsPixmapItem*
Renderer::renderGameObject(QList<QMap<GameObject::DataRole, QVariant>>& dt_ls) {
    QGraphicsPixmapItem* tile;
    //QList<QMap<GameObject::DataRole, QVariant>> dt_ls = object->getAllData();
    tile = new QGraphicsPixmapItem(renderTile(dt_ls[0]));
    QGraphicsPixmapItem *item;
    dt_ls.pop_front();

    for (auto data : dt_ls) {
        switch (data[GameObject::DataRole::Type].toInt()) {
        case static_cast<int>(GameObject::ObjectType::Tile):
            item = new QGraphicsPixmapItem(renderTile(data));
            item->setParentItem(tile);
        case static_cast<int>(GameObject::ObjectType::Doorway):
            item = new QGraphicsPixmapItem(renderDoorway(data));
            item->setParentItem(tile);
        case static_cast<int>(GameObject::ObjectType::HealthPack):
            item = new QGraphicsPixmapItem(renderHealthPack(data));
            item->setParentItem(tile);
        case static_cast<int>(GameObject::ObjectType::Protagonist):
            item = new QGraphicsPixmapItem(renderProtagonist(data));
            item->setParentItem(tile);
            //        case GameObject::ObjectType::Enemy:
            //            return renderEnemy(data);
            //        case GameObject::ObjectType::PoisonEnemy:
            //            return renderEnemy(data);
            //        case GameObject::ObjectType::MovingEnemy:
            //            return renderMovingEnemy(data);
        default:
            // Handle default case or unknown types
            item = new QGraphicsPixmapItem(renderEnemy(data));
            item->setParentItem(tile);
        }
    }

    return tile;
}
