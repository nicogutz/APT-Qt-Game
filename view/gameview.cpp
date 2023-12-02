#include "GameView.h"
#include <QGraphicsPixmapItem>

GameView::GameView(int rows, int columns, QObject *parent)
    : QGraphicsScene(parent), m_rows(rows), m_columns(columns) {
    // Initialize the m_tiles with empty shared pointers
    for (int i = 0; i < m_rows; ++i) {
        QList<QSharedPointer<QGraphicsPixmapItem>> rowItems(m_columns);
        m_tiles.append(rowItems);
    }
}

void GameView::createScene(const QList<QList<QSharedPointer<GameObject>>>& gameObjects, QSharedPointer<Renderer> renderer) {
    if (!renderer.isNull()) {
        setRenderer(renderer);
    }

    if (m_renderer.isNull()) {
        return;
    }

    for (int x = 0; x < m_rows; ++x) {
        for (int y = 0; y < m_columns; ++y) {
            if (x < gameObjects.size() && y < gameObjects[x].size() && !gameObjects[x][y].isNull()) {
                QPixmap pixmap = m_renderer->renderGameObject(gameObjects[x][y]);
                QSharedPointer<QGraphicsPixmapItem> item(new QGraphicsPixmapItem(pixmap));
                item->setPos(x * pixmap.width(), y * pixmap.height());
                addItem(item.data());  // Add the QGraphicsPixmapItem to the scene
                m_tiles[x][y] = item;  // Store the shared pointer in m_tiles
            }
        }
    }
}

void GameView::updateTile(const QSharedPointer<GameObject>& gameObject, int x, int y) {
    if (m_renderer.isNull() || x >= m_rows || y >= m_columns || gameObject.isNull()) {
        // Renderer not set, invalid position, or null GameObject
        return;
    }

    QPixmap pixmap = m_renderer->renderGameObject(gameObject);
    if (!m_tiles[x][y].isNull()) {
        m_tiles[x][y]->setPixmap(pixmap);
    } else {
        QSharedPointer<QGraphicsPixmapItem> item(new QGraphicsPixmapItem(pixmap));
        item->setPos(x * pixmap.width(), y * pixmap.height());
        addItem(item.data());  // Add the QGraphicsPixmapItem to the scene
        m_tiles[x][y] = item;  // Store the shared pointer in m_tiles
    }
}

void GameView::setRenderer(QSharedPointer<Renderer> newRenderer) {
    m_renderer = newRenderer;
}
