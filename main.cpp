#include "view/renderer/colorrenderer.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QSharedPointer>

#include <model/gameobject.h>

#include "view/gameview.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    const int gridSize = 11;
    GameView scene(gridSize, gridSize);
    QGraphicsView view(&scene);
    ColorRenderer renderer;

    const int cellSize = 50; // Assuming cell size defined in ColorRenderer

    // Create grid of game objects
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            QList<QMap<GameObject::DataRole, QVariant>> objectDataList;

            // Default to Tile for each cell
            QMap<GameObject::DataRole, QVariant> tileData;
            tileData[GameObject::DataRole::Type] = QVariant::fromValue(GameObject::ObjectType::Tile);
            tileData[GameObject::DataRole::Energy] = (x + 1) * (50 / gridSize) + (y + 1) * (50 / gridSize);
            objectDataList.append(tileData);

            GameObject::ObjectType specialType = GameObject::ObjectType::Tile;
            if (x == 0 && y == gridSize - 1) { // Top right: Enemy
                specialType = GameObject::ObjectType::Enemy;
            } else if (x == 0 && y == 0) { // Top left: Protagonist
                specialType = GameObject::ObjectType::Protagonist;
            } else if (x == gridSize - 1 && y == gridSize - 1) { // Bottom right: Doorway
                specialType = GameObject::ObjectType::Doorway;
            } else if (x == gridSize / 2 && y == gridSize / 2) { // Center: HealthPack
                specialType = GameObject::ObjectType::HealthPack;
            }

            if (specialType != GameObject::ObjectType::Tile) {
                QMap<GameObject::DataRole, QVariant> specialData;
                specialData[GameObject::DataRole::Type] = QVariant::fromValue(specialType);
                if (specialType == GameObject::ObjectType::Enemy) {
                    specialData[GameObject::DataRole::Health] = 50;
                    specialData[GameObject::DataRole::PoisonLevel] = 100;
                }
                if (specialType == GameObject::ObjectType::Protagonist) {
                    specialData[GameObject::DataRole::Health] = 100;
                    specialData[GameObject::DataRole::Energy] = 90;
                }
                if (specialType == GameObject::ObjectType::HealthPack) {
                    specialData[GameObject::DataRole::Health] = 75;
                }
                objectDataList.append(specialData);
            }

            // Render the game object and add it to the scene
            QGraphicsPixmapItem* item = renderer.renderGameObject(objectDataList);
            item->setPos(x * cellSize, y * cellSize);
            scene.addItem(item);
            objectDataList.empty();
        }
    }

    view.show();
    return app.exec();
}
