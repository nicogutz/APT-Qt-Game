#ifndef GENERICPOISONINGBEHAVIOR_H
#define GENERICPOISONINGBEHAVIOR_H

#include <model/behaviors/poison.h>

class GenericPoisoningBehavior : public Poison {
public:
    GenericPoisoningBehavior(QSharedPointer<GameObject> owner)
        : Poison(owner) {};

    int poison(const QSharedPointer<GameObject> &target) override;
};

#endif // GENERICPOISONINGBEHAVIOR_H
