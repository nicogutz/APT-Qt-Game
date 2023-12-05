#include "renderer.h"

Renderer::Renderer() {
}

QPixmap
Renderer::renderGameObject(const QSharedPointer<GameObject>& object) {

    for (auto data : object->getAllData()) {
        switch (data[GameObject::DataRole::Type].toInt()) {
        case static_cast<int>(GameObject::ObjectType::Tile):
            return renderTile(data);
        case static_cast<int>(GameObject::ObjectType::Doorway):
            return renderDoorway(data);
        case static_cast<int>(GameObject::ObjectType::HealthPack):
            return renderHealthPack(data);
        case static_cast<int>(GameObject::ObjectType::Protagonist):
            return renderProtagonist(data);
            //        case GameObject::ObjectType::Enemy:
            //            return renderEnemy(data);
            //        case GameObject::ObjectType::PoisonEnemy:
            //            return renderEnemy(data);
            //        case GameObject::ObjectType::MovingEnemy:
            //            return renderMovingEnemy(data);
        default:
            // Handle default case or unknown types
            return renderEnemy(data);
        }
    }
}
