#pragma once

#include "Drawable.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class Renderer
{
public:
    Renderer(unsigned int width, unsigned int height);

    void addDrawable(std::weak_ptr<Drawable> drawable);
    void render();
    [[nodiscard]] sf::RenderWindow& getWindow();

private:
    sf::RenderWindow window;
    std::vector<std::weak_ptr<Drawable>> drawables;
};
