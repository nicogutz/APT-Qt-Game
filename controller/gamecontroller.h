#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <iostream>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include <QCoreApplication>
#include <qdatetime.h>

#include <QDateTime>

#include "model/modelfactory.h"
#include "model/gameobjectmodel.h"
#include "view/gameview.h"
#include <model/behaviors/concrete/poison/genericpoisonablebehavior.h>
#include <model/behaviors/concrete/poison/genericpoisoningbehavior.h>
#include <pathfinder_class.h>
#include <model/behaviors/health.h>
#include "model/behaviors/attack.h"
#include "view/renderer/spriterenderer.h"
#include "view/renderer/textrenderer.h"
#include "view/renderer/colorrenderer.h"



class GameWindow;

/**
 * @brief The GameController class
 */
class GameController : public QGraphicsView {
    Q_OBJECT
public:
    /**
     * @brief The State enum
     */
    enum class State {
        Running,
        Automatic,
        Paused,
        GameOver,
    };

    enum class View {
        Text,
        Sprite,
        Color,
    };
    /**
     * @brief GameController
     */
    GameController();
    void startGame();


    void findAndMoveTo(int x, int y);

    /**
     * @brief characterMove
     * @param to
     */
    void characterMove(Direction to);
    /**
     * @brief characterAtttack
     * @param to
     */
    void characterAtttack();
    void path_finder(int rows);

    void updateEnergy();
    void updateHealth();
    void updateLevel(Direction direction);
    void updateGameView(View view);

    void dataChanged(QMap<DataRole, QVariant> objectData);

    void disconnectCurrentModel();
    void connectCurrentModel();
    void emitLevelUpdates();

    void createNewLevel(int level);

    void setState(State new_state);
    State getState();
    View getGameView(){return m_gameView;}
    QSharedPointer<GameView> getView();
    void setView(QSharedPointer<GameView> view);


signals:
    /**
     * @brief tick Emitted when a turn is complete.
     * @param clock The count of clocks so far
     */
    void tick();
    /**
     * @brief gameOver This is emitted when the game is over.
     */
    void gameOver();
    /**
     * @brief stateChanged This is emitted when the game state changes
     * @param stateChanged state The new game state
     */

    void stateChanged(State state);
    void energyUpdated(int energy);
    void healthUpdated(int health);
    void enemiesUpdated(int enemies);
    void healthPacksUpdated(int health_packs);
    void levelUpdated(int level);

private:
    ObjectModelFactory factory;
    /**
     * @brief m_model
     */
    QList<GameObjectModel *> m_models;
    /**
     * @brief m_view
     */
    QSharedPointer<GameView> m_view;

    /**
     * @brief m_character
     */
    QPointer<GameObject> m_character;

    int m_gameLevel;
    State m_gameState;
    View m_gameView;

    int m_health_packs;
    int m_enemies;
};

#endif // GAMECONTROLLER_H
