#include "newlevelonstep.h"

bool NewLevelOnStep::getSteppedOn(const QPointer<GameObject> &source) {
    int srcType = source->getData(DataRole::Type).toInt();

    if(srcType == static_cast<int>(ObjectType::Protagonist))
        emit newLevel(source);

    return true;
}
