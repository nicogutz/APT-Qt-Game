#ifndef NEWLEVELONSTEP_H
#define NEWLEVELONSTEP_H

#include "genericwalkablebehavior.h"

class NewLevelOnStep : public QObject, public GenericWalkableBehavior {
    Q_OBJECT

public:
    NewLevelOnStep(QSharedPointer<GameObject> owner)
        : GenericWalkableBehavior(owner) {};
    bool getSeppedOn(const QSharedPointer<GameObject> &source) override;
signals:
    void newLevel(const QSharedPointer<GameObject> &source);
};

#endif // NEWLEVELONSTEP_H
