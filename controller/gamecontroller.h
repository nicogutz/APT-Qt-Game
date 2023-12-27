#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <iostream>

#include "model/modelfactory.h"
#include "model/gameobjectmodel.h"
#include "view/gameview.h"
#include "model/behaviors/concrete/movement/poisononstepbehavior.h"
#include "model/behaviors/concrete/movement/genericmovebehavior.h"
#include "view/renderer/textrenderer.h"
#include "view/renderer/colorrenderer.h"
#include "view/renderer/spriterenderer.h"
#include <model/behaviors/concrete/poison/genericpoisonablebehavior.h>
#include <model/behaviors/concrete/poison/genericpoisoningbehavior.h>
#include <pathfinder_class.h>>

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
        BeforeFirstGame,
        Running,
        BetweenLevels,
        Paused,
        Suspended,
        GameOver,
    };

    enum class Mode {
        Automatic,
        Manual,
    };

    enum class View {
        Text,
        Graphical,
        Color,
    };
    /**
     * @brief GameController
     */
    GameController();
    void startGame();

    QSharedPointer<GameView> getView();
    void setView(QSharedPointer<GameView> view);

    void findAndMoveTo(int x, int y);

public slots:

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
    void characterHealth();

    void updateLevel(unsigned int level);
    void updateGameState(State new_state);
    void updateGameView(View view);
    void updateGameMode(Mode mode);

    // void updateHealthPacks();
    // void updateEnemies();

signals:
    /**
     * @brief tick Emitted when a turn is complete.
     * @param clock The count of clocks so far
     */
    void tick(unsigned long int clock);
    /**
     * @brief gameOver This is emitted when the game is over.
     */
    void gameOver();
    /**
     * @brief levelChanged This is emitted when the level changes.
     * @param level The new level
     */
    void levelChanged(unsigned int level);

    /**
     * @brief scoreChanged This is emitted when the source changes
     * @param score The new score
     */
    void scoreChanged(unsigned int score);
    /**
     * @brief livesChanged This is emitted when the lives change
     * @param lives The new lives
     */
    void livesChanged(unsigned int lives);
    /**
     * @brief timeChanged This is emitted when the time changes
     * @param time The new time value
     */
    void timeChanged(unsigned int time);
    /**
     * @brief stateChanged This is emitted when the game state changes
     * @param stateChanged state The new game state
     */
    void stateChanged(State state);

private:
    /**
     * @brief m_model
     */
    QList<QPointer<GameObjectModel>> m_model;
    /**
     * @brief m_view
     */
    QSharedPointer<GameView> m_view;

    /**
     * @brief m_character
     */
    QPointer<GameObject> m_character;
    GameObjectModel *model;

    unsigned int m_gameLevel;
    Mode m_gameMode;
    State m_gameState;
    View m_gameView;
};

#endif // GAMECONTROLLER_H
