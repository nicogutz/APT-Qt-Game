#include "gameview.h"
#include <QGraphicsPixmapItem>

GameView::GameView(int rows, int columns, QObject *parent)
    : QGraphicsScene(parent)
    , m_rows(rows)
    , m_columns(columns) {
    // Initialize the m_tiles with empty shared pointers
    for(int i = 0; i < m_rows; ++i) {
        QList<QSharedPointer<QGraphicsPixmapItem>> rowItems(m_columns);
        m_tiles.append(rowItems);
    }
}

void GameView::createScene(
  const QList<QList<QList<QMap<DataRole, QVariant>>>> &gameObjects,
  QSharedPointer<Renderer> renderer) {
    if(!renderer.isNull()) {
        setRenderer(renderer);
    }

    if(m_renderer.isNull()) {
        return;
    }

    for(int x = 0; x < m_rows; ++x) {
        for(int y = 0; y < m_columns; ++y) {
            if(x < gameObjects.size() && y < gameObjects[x].size()
               && !gameObjects[x][y].empty()) {
                auto item = QSharedPointer<QGraphicsPixmapItem>(m_renderer->renderGameObjects(gameObjects[x][y]));

                item->setPos(x * item->pixmap().width(), y * item->pixmap().height());
                m_tiles[x][y] = item; // Store the shared pointer in m_tiles
                addItem(item.get());
            }
        }
    }
}

void GameView::updateObject(const QMap<DataRole, QVariant> gameObject) {
    QPoint point = gameObject[DataRole::Position].toPoint();

    auto item = QSharedPointer<QGraphicsPixmapItem>(m_renderer->renderGameObject(gameObject));

    item->setPos(point.x() * item->pixmap().width(), point.y() * item->pixmap().height());
    m_tiles[point.x()][point.y()] = item;
}

void GameView::setRenderer(QSharedPointer<Renderer> newRenderer) {
    m_renderer = newRenderer;
}

void GameView::dataChanged(QMap<DataRole, QVariant> objectData) {
    if(objectData[DataRole::LatestChange].value<DataRole>() == DataRole::Position) {
        auto position = objectData[DataRole::Position].toPoint();
        auto direction = objectData[DataRole::Direction].toInt();
        double angleRad = (direction)*M_PI / 180;
        int x = position.x() - round(cos(angleRad));
        int y = position.y() + round(sin(angleRad));
        auto changedObject = m_tiles[x][y]->childItems()[0];

        changedObject->setParentItem(m_tiles[position.x()][position.y()].get());
    } else if(objectData[DataRole::LatestChange].value<DataRole>() == DataRole::Direction) {
        auto position = objectData[DataRole::Position].toPoint();
        auto changedObject = m_tiles[position.x()][position.y()]->childItems()[0];

        changedObject->setTransformOriginPoint(changedObject->boundingRect().width() / 2,
                                               changedObject->boundingRect().height() / 2);
        changedObject->setRotation(objectData[DataRole::Direction].toInt() - 90);
    }
}
