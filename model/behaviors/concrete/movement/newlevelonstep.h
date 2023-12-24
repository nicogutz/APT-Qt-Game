#ifndef NEWLEVELONSTEP_H
#define NEWLEVELONSTEP_H

#include "genericwalkablebehavior.h"

class NewLevelOnStep : public QObject, public GenericWalkableBehavior {
    Q_OBJECT

public:
    NewLevelOnStep(QPointer<GameObject> owner)
        : GenericWalkableBehavior(owner) {};
    bool getSteppedOn(const QPointer<GameObject> &source) override;
signals:
    void newLevel(const QPointer<GameObject> &source);
};

#endif // NEWLEVELONSTEP_H
