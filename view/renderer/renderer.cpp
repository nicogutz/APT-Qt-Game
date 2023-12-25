#include "renderer.h"

Renderer::Renderer() {
}

QGraphicsPixmapItem *Renderer::renderGameObjects(QList<QMap<DataRole, QVariant>> objectDataList) {
    QGraphicsPixmapItem *tile = new QGraphicsPixmapItem(renderGameObject(objectDataList[0]));

    for(auto data : objectDataList.mid(1, -1)) {
        auto *obj = new QGraphicsPixmapItem(renderGameObject(data));
        obj->setParentItem(tile);
    }
    return tile;
}

QPixmap Renderer::renderGameObject(QMap<DataRole, QVariant> objectData) {
    switch(objectData[DataRole::Type].value<ObjectType>()) {
    case ObjectType::Tile:
        return renderTile(objectData);
        break;
    case ObjectType::Doorway:
        return renderDoorway(objectData);
        break;
    case ObjectType::HealthPack:
        return renderHealthPack(objectData);
        break;
    case ObjectType::Protagonist:
        return renderProtagonist(objectData);
        break;
    default:
        // Handle default case or unknown types
        return renderEnemy(objectData);
        break;
    }
}

QPixmap Renderer::rotatePixmap(const QPixmap &originalPixmap, int direction) {
    QTransform transformation;
    transformation.rotate(direction);

    return originalPixmap.transformed(transformation);
}
