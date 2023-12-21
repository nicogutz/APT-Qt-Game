#include "view/renderer/colorrenderer.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QSharedPointer>

#include <model/gameobject.h>

#include "ui_gamewindow.h"
#include "view/gamewindow.h"
#include "controller/gamecontroller.h"

#include "view/gameview.h"
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <iostream>
#include <QProcess>
#include <view/renderer/textrenderer.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main classes of the gzme: GameWindow, GameView, GameController
    GameWindow w;
    auto widget = QSharedPointer<QWidget>(new QWidget(&w));
    auto gameController = w.getController();
    Ui::GameWindow* ui = w.getUI();
    QSharedPointer<GameView> view = gameController->getView();


    const int gridSize = 11;

    //ui->graphicsView->setScene(view.data());


    //QGraphicsView view(&scene);
    TextRenderer renderer;
    const int cellSize = 50;
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
                    specialData[GameObject::DataRole::Direction] = QVariant(int (GameObject::Direction::Up));
                }
                if (specialType == GameObject::ObjectType::Protagonist) {
                    specialData[GameObject::DataRole::Health] = 10;
                    specialData[GameObject::DataRole::Energy] = 20;
                    specialData[GameObject::DataRole::Direction] = QVariant(int (GameObject::Direction::Left));
                }
                if (specialType == GameObject::ObjectType::HealthPack) {
                    specialData[GameObject::DataRole::Health] = 75;
                }
                objectDataList.append(specialData);
            }

            // Render the game object and add it to the scene
            QGraphicsPixmapItem* item = renderer.renderGameObject(objectDataList);
            item->setPos(x * cellSize, y * cellSize);
            view->addItem(item);
            objectDataList.empty();
        }
    }

    gameController->show();

    // Connect Signals and slots
    QObject::connect(gameController.data(), &GameController::levelChanged, &w, &GameWindow::updateLevel);

    QObject::connect(ui->textEdit, &QLineEdit::returnPressed, &w, &GameWindow::processCommand);

    QObject::connect(ui->quit_game, &QPushButton::clicked, &app, &QApplication::quit);
    QObject::connect(ui->rerun_game_2, &QPushButton::clicked, []
                     {  QProcess::startDetached(qApp->arguments()[0], qApp->arguments());  }
                     );


    w.show();
    return app.exec();

    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}



