#ifndef GENERICHEALTHBEHAVIOR_H
#define GENERICHEALTHBEHAVIOR_H

#include <model/behaviors/health.h>

class GenericHealthBehavior : public QObject, Health {
    Q_OBJECT
public:
    GenericHealthBehavior(QSharedPointer<GameObject> owner)
        : Health(owner) {};

    int getHealthChanged(int amount) override;
    void die() override;
signals:
    void objectKilled(const QSharedPointer<GameObject> &object);
};

#endif // GENERICHEALTHBEHAVIOR_H
