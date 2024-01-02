#include "renderer.h"

#include <QPropertyAnimation>

Renderer::Renderer() {
}

GamePixmapItem *Renderer::renderGameObjects(QList<QMap<DataRole, QVariant>> objectDataList) {
    auto *tile = renderGameObject(objectDataList[0]);
    tile->setData((int)DataRole::Type, objectDataList[0][DataRole::Type]);

    for(const auto &data : objectDataList.mid(1, -1)) {
        auto *obj = renderGameObject(data);
        obj->setData((int)DataRole::Type, data[DataRole::Type]);
        obj->setParentItem(tile);
    }
    return tile;
}

void Renderer::renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) {
    switch(objectData[DataRole::Type].value<ObjectType>()) {
    case ObjectType::Tile:
        item->setPixmap(renderTile(objectData));
        break;
    case ObjectType::Doorway:
        item->setPixmap(renderDoorway(objectData));
        break;
    case ObjectType::HealthPack:
        item->setPixmap(renderHealthPack(objectData));
        break;
    case ObjectType::Protagonist:
        item->setPixmap(renderProtagonist(objectData));
        break;
    case ObjectType::Enemy:
        item->setPixmap(renderEnemy(objectData));
        break;
    case ObjectType::PoisonEnemy:
        item->setPixmap(renderPEnemy(objectData));
        break;
    case ObjectType::MovingEnemy:
        item->setPixmap(renderMovingEnemy(objectData));
        break;
    default:
        item->setPixmap(renderEnemy(objectData));
        break;
    }
}

GamePixmapItem *Renderer::renderGameObject(QMap<DataRole, QVariant> objectData) {
    auto *obj = new GamePixmapItem();
    renderGameObject(objectData, obj);
    return obj;
}

QPixmap Renderer::rotatePixmap(const QPixmap &originalPixmap, int direction) {
    QTransform transformation;
    transformation.rotate(-direction + 90);
    return originalPixmap.transformed(transformation);
}
