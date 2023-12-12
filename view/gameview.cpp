#include "gameview.h"
#include <QGraphicsPixmapItem>

GameView::GameView(int rows, int columns, QObject* parent)
    : QGraphicsScene(parent)
    , m_rows(rows)
    , m_columns(columns) {
    // Initialize the m_tiles with empty shared pointers
    for (int i = 0; i < m_rows; ++i) {
        QList<QSharedPointer<QGraphicsPixmapItem>> rowItems(
            m_columns);
        m_tiles.append(rowItems);
    }
}

void GameView::createScene(
    const QList<QList<QSharedPointer<GameObject>>>& gameObjects,
    QSharedPointer<Renderer> renderer) {
    if (!renderer.isNull()) {
        setRenderer(renderer);
    }

    if (m_renderer.isNull()) {
        return;
    }

    for (int x = 0; x < m_rows; ++x) {
        for (int y = 0; y < m_columns; ++y) {
            if (x < gameObjects.size() && y < gameObjects[x].size()
                && !gameObjects[x][y].isNull()) {
                QList<QMap<GameObject::DataRole, QVariant>> gameObjectData = gameObjects[x][y]->getAllData();

                auto item
                    = QSharedPointer<QGraphicsPixmapItem>(m_renderer->renderGameObject(gameObjectData));

                item->setPos(x * item->pixmap().width(), y * item->pixmap().height());
                m_tiles[x][y]
                    = item; // Store the shared pointer in m_tiles
            }
        }
    }
}

void GameView::updateTile(
    const QSharedPointer<GameObject>& gameObject) {
    int x = gameObject->getData(GameObject::DataRole::X_Position)
                .toInt();
    int y = gameObject->getData(GameObject::DataRole::Y_Position)
                .toInt();
    QList<QMap<GameObject::DataRole, QVariant>> gameObjectData = gameObject->getAllData();

    auto item
        = QSharedPointer<QGraphicsPixmapItem>(m_renderer->renderGameObject(gameObjectData));

    item->setPos(x * item->pixmap().width(), y * item->pixmap().height());

    m_tiles[x][y] = item;
}

void GameView::setRenderer(QSharedPointer<Renderer> newRenderer) {
    m_renderer = newRenderer;
}
