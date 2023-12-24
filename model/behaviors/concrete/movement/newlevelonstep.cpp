#include "newlevelonstep.h"
bool NewLevelOnStep::getSteppedOn(const QPointer<GameObject> &source) {
    ObjectType srcType = source->getData(DataRole::Type).value<ObjectType>();

    if(srcType == ObjectType::Protagonist)
        emit newLevel(source);

    return true;
}
