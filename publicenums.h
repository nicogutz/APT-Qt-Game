#ifndef PUBLICENUMS_H
#define PUBLICENUMS_H
#include <cstdint>
#include <QMetaType>

enum class ObjectType : char {
    Tile = 0,
    Doorway = 1,
    HealthPack = 2,
    Protagonist = 50,
    Enemy = 100,
    PoisonEnemy = 101,
    FireEnemy = 102,
};
enum class DataRole : int {
    Type,

    Health,
    Energy,
    Strength,

    PoisonLevel,
    FireLevel,

    Visibility,

    Position,
    Direction,

    LatestChange,
    ChangeDirection,
};
enum class Direction : int {
    Right = 0,
    TopRight = 45,
    Up = 90,
    TopLeft = 135,
    Left = 180,
    BottomLeft = 225,
    Down = 270,
    BottomRight = 315,
};

const Direction EnumDirectionVector[] = {
  Direction::TopLeft,
  Direction::Up,
  Direction::TopRight,
  Direction::Left,
  Direction::Right,
  Direction::BottomLeft,
  Direction::Down,
  Direction::BottomRight,
};

Q_DECLARE_METATYPE(ObjectType);
Q_DECLARE_METATYPE(DataRole);
Q_DECLARE_METATYPE(Direction);

#endif // PUBLICENUMS_H
