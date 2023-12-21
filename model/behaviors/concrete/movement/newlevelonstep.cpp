#include "newlevelonstep.h"

bool NewLevelOnStep::getSteppedOn(const QSharedPointer<GameObject> &source) {
    int srcType = source->getData(GameObject::DataRole::Type).toInt();

    if(srcType == static_cast<int>(GameObject::ObjectType::Protagonist))
        emit newLevel(source);

    return true;
}
