#pragma once

using GoId = unsigned int;

struct Position
{
    float x;
    float y;
};

using Rotation = float;

class GameObject
{
public:
    ~GameObject() = default;

    [[nodiscard]] virtual GoId getId() const = 0;
    virtual void move(Position position) = 0;
    virtual void rotate(Rotation rotation) = 0;
};
