#pragma once

#include <InputEvent.hpp>
#include <InputSource.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

class SfmlInputSource : public InputSource
{
public:
    explicit SfmlInputSource(sf::RenderWindow& inputWindow);

    [[nodiscard]] std::vector<InputEvent> pollEvents() override;

private:
    sf::RenderWindow& window;

    static InputEvent translateToInputEvent(const sf::Event& sfEvent);
    static MouseButton translateToMouseButton(const sf::Mouse::Button& sfButton);
    static Key translateToKeyData(const sf::Keyboard::Key& sfKey);
};
