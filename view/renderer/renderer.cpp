#include "renderer.h"

#include <QPropertyAnimation>

Renderer::Renderer() {
}

GamePixmapItem *Renderer::renderGameObjects(QList<QMap<DataRole, QVariant>> objectDataList) {
    GamePixmapItem *tile = renderGameObject(objectDataList[0]);

    for(const auto &data : objectDataList.mid(1, -1)) {
        auto *obj = renderGameObject(data);
        obj->setData(DataRole::Type, data[DataRole::Type]);
        obj->setParentItem(tile);
    }
    return tile;
}

GamePixmapItem *Renderer::renderGameObject(QMap<DataRole, QVariant> objectData) {
    switch(objectData[DataRole::Type].value<ObjectType>()) {
    case ObjectType::Tile:
        return renderTile(objectData);
    case ObjectType::Doorway:
        return renderDoorway(objectData);
    case ObjectType::HealthPack:
        return renderHealthPack(objectData);
    case ObjectType::Protagonist:
        return renderProtagonist(objectData);
    case ObjectType::Enemy:
        return renderEnemy(objectData);
    case ObjectType::PoisonEnemy:
        return renderPEnemy(objectData);
    case ObjectType::MovingEnemy:
        return renderMovingEnemy(objectData);
    default:
        return renderEnemy(objectData);
    }
}

QPixmap Renderer::rotatePixmap(const QPixmap &originalPixmap, int direction) {
    QTransform transformation;
    transformation.rotate(-direction + 90);
    return originalPixmap.transformed(transformation);
}
