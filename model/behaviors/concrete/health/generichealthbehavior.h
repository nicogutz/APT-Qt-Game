#ifndef GENERICHEALTHBEHAVIOR_H
#define GENERICHEALTHBEHAVIOR_H

#include <model/behaviors/health.h>

class GenericHealthBehavior : public QObject, public Health {
    Q_OBJECT
public:
    GenericHealthBehavior(QPointer<GameObject> owner)
        : Health(owner) {};

    int getHealthChanged(int amount) override;
    void die() override;
};

#endif // GENERICHEALTHBEHAVIOR_H
