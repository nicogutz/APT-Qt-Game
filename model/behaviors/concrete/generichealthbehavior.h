#ifndef GENERICHEALTHBEHAVIOR_H
#define GENERICHEALTHBEHAVIOR_H

#include <model/behaviors/health.h>

class GenericHealthBehavior : public QObject, Health {
    Q_OBJECT
public:
    GenericHealthBehavior(QSharedPointer<GameObject> owner)
        : m_owner(owner) {};

    int getHealthChanged(int amount) override;
    bool getIsHealable() const;
    void setIsHealable(bool newIsHealable);

signals:
    void objectKilled(const QSharedPointer<GameObject>& object);

private:
    QSharedPointer<GameObject> m_owner;
};

#endif // GENERICHEALTHBEHAVIOR_H
