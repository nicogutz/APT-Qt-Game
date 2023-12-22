#ifndef GENERICMOVEBEHAVIOR_H
#define GENERICMOVEBEHAVIOR_H

#include <model/behaviors/movement.h>

class GenericMoveBehavior : public Movement {
public:
    GenericMoveBehavior(QSharedPointer<GameObject> owner)
        : Movement(owner) {
        bool data_missing
          // clang-format off
          = (  owner->getData(DataRole::X_Position).isNull() ||
               owner->getData(DataRole::Y_Position).isNull() ||
               owner->getData(DataRole::Direction).isNull()
             );
        if(data_missing) {
            // clang-format on
            throw "Data Not Correct";
        }
    };
    bool stepOn(QSharedPointer<GameObject> target) override;
    bool stepOn(Direction direction) override;
};

#endif // GENERICMOVEBEHAVIOR_H
