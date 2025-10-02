#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

class Drawable
{
public:
    ~Drawable() = default;

    virtual void draw(sf::RenderTarget& target) const = 0;
};
