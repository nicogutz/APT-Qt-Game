#include "gameview.h"
#include <QGraphicsPixmapItem>

GameView::GameView(QObject *parent)
    : QGraphicsScene(parent) {
    // Initialize the m_tiles with empty shared pointers
}

void GameView::createScene(
  const QList<QList<QList<QMap<DataRole, QVariant>>>> &gameObjects,
  QSharedPointer<Renderer> renderer) {
    setRenderer(renderer);
    if(!m_tiles.empty()) {
        clear();
    }
    m_tiles = QList<QList<QGraphicsPixmapItem *>>(gameObjects.size());
    for(int x = 0; x < gameObjects.size(); ++x) {
        QList<QGraphicsPixmapItem *> rowItems(gameObjects[0].size());
        m_tiles[x] = (rowItems);

        for(int y = 0; y < gameObjects[0].size(); ++y) {
            if(x < gameObjects.size() && y < gameObjects[x].size()
               && !gameObjects[x][y].empty()) {
                auto *item = m_renderer->renderGameObjects(gameObjects[x][y]);

                item->setPos(x * item->pixmap().width(), y * item->pixmap().height());
                m_tiles[x][y] = item; // Store the shared pointer in m_tiles
                addItem(item);
            }
        }
    }
}

void GameView::setRenderer(QSharedPointer<Renderer> newRenderer) {
    m_renderer = std::move(newRenderer);
}
QGraphicsItem *GameView::getPixmapItem(int x, int y, QVariant type) {
    auto tile = m_tiles[x][y];
    switch(type.value<ObjectType>()) {
    case ObjectType::Tile:
        return tile;
    default:
        for(auto child : tile->childItems()) {
            if(child->data(static_cast<int>(DataRole::Type)) == type) {
                return child;
            }
        }
        return nullptr;
    }
}
void GameView::dataChanged(QMap<DataRole, QVariant> objectData) {
    auto position = objectData[DataRole::Position].toPoint();

    if(objectData[DataRole::LatestChange].value<DataRole>() == DataRole::Position) {
        auto direction = objectData[DataRole::Direction].toInt();
        double angleRad = (direction)*M_PI / 180;
        int x = position.x() - round(cos(angleRad));
        int y = position.y() + round(sin(angleRad));
        auto changedObject = getPixmapItem(x, y, objectData[DataRole::Type]);
        changedObject->setParentItem(getPixmapItem(position.x(), position.y(), QVariant::fromValue<ObjectType>(ObjectType::Tile)));
    } else if(objectData[DataRole::Destroyed].toBool()) {
        delete getPixmapItem(position.x(), position.y(), objectData[DataRole::Type]);
    } else {
        auto *obj = getPixmapItem(position.x(), position.y(), objectData[DataRole::Type]);
        dynamic_cast<QGraphicsPixmapItem *>(obj)->setPixmap(m_renderer->renderGameObject(objectData));
    }
}
