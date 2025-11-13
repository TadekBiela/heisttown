#pragma once

using GoId = unsigned int;

class GameObject
{
public:
    ~GameObject() = default;

    [[nodiscard]] virtual GoId getId() const = 0;
    virtual void move(float x, float y) = 0;
    virtual void rotate(float angle) = 0;
};
