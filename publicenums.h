#ifndef PUBLICENUMS_H
#define PUBLICENUMS_H
enum class ObjectType {
    Tile = 0,
    Doorway = 1,
    HealthPack = 2,
    Protagonist = 50,
    Enemy = 100,
    PoisonEnemy = 101,
    FireEnemy = 102,
};
enum class DataRole {
    Type,

    Health,
    Energy,
    Strength,

    PoisonLevel,
    FireLevel,

    Visibility,

    X_Position,
    Y_Position,
    Direction,

    LatestChange,
    ChangeDirection,
};
enum class Direction {
    TopLeft = 45,
    Up = 90,
    TopRight = 135,
    Left = 180,
    Right = 0,
    BottomLeft = 225,
    Bottom = 270,
    BottomRight = 315,
};
#endif // PUBLICENUMS_H
