#include "gamecontroller.h"

GameController::GameController()
    : QGraphicsView()
    , m_gameMode(Mode::Manual)
    , m_gameState(State::Running)
    , m_gameView(View::Color)
    , m_gameLevel(1)

{

}

void GameController::startGame(){
    ObjectModelFactory factory;
    // create world with 6 Enemies 5 health packs and 3 PEnemies
    model = factory.createModel(":/images/worldmap.png", 6, 5, 0.5f);

    model->setParent(this);
    m_character = factory.getPro(); // this is temporary, could probably be done in a better ways
    m_model = QList<QPointer<GameObjectModel>>({model});
    m_view = QSharedPointer<GameView>::create(this);
    m_view->createScene(model->getAllData(), QSharedPointer<ColorRenderer>::create());
    connect(model, &GameObjectModel::dataChanged, m_view.get(), &GameView::dataChanged);
    this->show();

    if (m_gameMode==Mode::Automatic){

        auto path = factory.pathFinder();
        /*
        for (int move : path) {
            Direction direction;
            switch (move) {
            case 0: direction = Direction::Up; break;
            case 1: direction = Direction::TopRight; break;
            case 2: direction = Direction::Right; break;
            case 3: direction = Direction::BottomRight; break;
            case 4: direction = Direction::Down; break;
            case 5: direction = Direction::BottomLeft; break;
            case 6: direction = Direction::Left; break;
            case 7: direction = Direction::TopLeft; break;
            default:
                // Handle invalid move
                qDebug() << "Invalid move in path: " << move;
                continue;
            }
            characterMove(direction);
        }*/
    }
}

void GameController::characterMove(Direction to) {
    if(m_gameState != State::Paused && m_gameMode != Mode::Automatic) {
        m_character->getBehavior<Movement>()->stepOn(to);
        emit tick(0);
    }
}

void GameController::characterAtttack() {
    if(m_gameState != State::Paused) {
        auto attack = m_character->getBehavior<Attack>();
        if(attack) {
            attack->attack();
        }
    }
}


void GameController::characterHealth() {
    if(m_gameState != State::Paused) {
        auto health = m_character->getBehavior<Health>();

    }
}




void GameController::updateGameState(State new_state) {
    if(m_gameState != new_state) {
        m_gameState = new_state;
    }
}

void GameController::updateLevel(unsigned int level) {
    m_gameLevel = level;

}
void GameController::updateGameView(View view){
    m_gameView = view;
    if (view==View::Graphical){

    } else if(view==View::Text){
        //m_view->createScene(model->getAllData(), QSharedPointer<TextRenderer>::create());
    }else{
        //m_view->createScene(model->getAllData(), QSharedPointer<ColorRenderer>::create());
    }


}

void GameController::updateGameMode(Mode mode){
    m_gameMode = mode;
}


QSharedPointer<GameView> GameController::getView() {
    return m_view;
}

void GameController::setView(QSharedPointer<GameView> view) {
    m_view = view;
}
