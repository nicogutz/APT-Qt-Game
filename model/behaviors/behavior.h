#ifndef BEHAVIOR_H
#define BEHAVIOR_H

class Behavior {
public:
    virtual ~Behavior() = 0;
    Behavior& operator=(const Behavior&) {
        return *this;
    };
};
#endif // BEHAVIOR_H
