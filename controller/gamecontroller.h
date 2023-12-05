#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <QGraphicsView>

#include <model/gameobjectmodel.h>

#include <view/gameview.h>

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
    /**
     * @brief GameController
     */
    GameController();
    QSharedPointer<GameView> getView();


public slots:

    /**
     * @brief characterMove
     * @param to
     */
    void characterMove(GameObject::Direction to);
    /**
     * @brief characterAtttack
     * @param to
     */
    void characterAtttack(GameObject::Direction to);

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
    QList<QSharedPointer<GameObjectModel>> m_model;
    /**
     * @brief m_view
     */
    QSharedPointer<GameView> m_view;

    /**
     * @brief m_character
     */
    QSharedPointer<GameObject> m_character;



};

#endif // GAMECONTROLLER_H








