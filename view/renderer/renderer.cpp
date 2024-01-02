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

GamePixmapItem *Renderer::renderGameObject(QMap<DataRole, QVariant> data) {
    auto *obj = new GamePixmapItem();
    obj->setData((int)DataRole::Type, data[DataRole::Type]);

    renderGameObject(data, obj);
    return obj;
}

void Renderer::renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) {
    switch(data[DataRole::Type].value<ObjectType>()) {
    case ObjectType::Tile:
        item->setPixmap(renderTile(data));
        break;
    case ObjectType::Doorway:
        item->setPixmap(renderDoorway(data));
        break;
    case ObjectType::HealthPack:
        item->setPixmap(renderHealthPack(data));
        break;
    case ObjectType::Protagonist:
        item->setPixmap(renderProtagonist(data));
        break;
    case ObjectType::Enemy:
        item->setPixmap(renderEnemy(data));
        break;
    case ObjectType::PoisonEnemy:
        item->setPixmap(renderPEnemy(data));
        break;
    case ObjectType::MovingEnemy:
        item->setPixmap(renderMovingEnemy(data));
        break;
    default:
        item->setPixmap(renderEnemy(data));
        break;
    }
}

QPixmap Renderer::rotatePixmap(const QPixmap &originalPixmap, int direction) {
    QTransform transformation;
    transformation.rotate(-direction + 90);
    return originalPixmap.transformed(transformation);
}
