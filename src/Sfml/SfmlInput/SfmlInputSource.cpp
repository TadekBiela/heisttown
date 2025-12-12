#include "SfmlInputSource.hpp"

SfmlInputSource::SfmlInputSource(sf::RenderWindow& inputWindow)
    : window(inputWindow)
{
}

std::vector<InputEvent> SfmlInputSource::pollEvents()
{
    std::vector<InputEvent> events;

    sf::Event sfEvent {};
    while (window.pollEvent(sfEvent))
    {
        auto event = translateToInputEvent(sfEvent);
        if (event.type != InputEventType::NotSupported)
        {
            events.push_back(event);
        }
    }

    return events;
}

// NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
InputEvent SfmlInputSource::translateToInputEvent(const sf::Event& sfEvent)
{
    InputEvent event;

    switch (sfEvent.type)
    {
        case sf::Event::MouseMoved:
        {
            event.type = InputEventType::MouseMove;
            event.data = MouseMoveData {
                static_cast<float>(sfEvent.mouseMove.x),
                static_cast<float>(sfEvent.mouseMove.y)
            };
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            event.type = InputEventType::MouseButtonPressed;
            event.data = MouseButtonData {
                translateToMouseButton(sfEvent.mouseButton.button),
                static_cast<float>(sfEvent.mouseButton.x),
                static_cast<float>(sfEvent.mouseButton.y)
            };
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            event.type = InputEventType::MouseButtonReleased;
            event.data = MouseButtonData {
                translateToMouseButton(sfEvent.mouseButton.button),
                static_cast<float>(sfEvent.mouseButton.x),
                static_cast<float>(sfEvent.mouseButton.y)
            };
            break;
        }
        case sf::Event::KeyPressed:
        {
            event.type = InputEventType::KeyPressed;
            event.data = KeyData { translateToKeyData(sfEvent.key.code) };
            break;
        }
        case sf::Event::KeyReleased:
        {
            event.type = InputEventType::KeyReleased;
            event.data = KeyData { translateToKeyData(sfEvent.key.code) };
            break;
        }
        case sf::Event::Closed:
        {
            event.type = InputEventType::Quit;
            break;
        }
        default:
        {
            break;
        }
    }

    return event;
}
// NOLINTEND(cppcoreguidelines-pro-type-union-access)

MouseButton SfmlInputSource::translateToMouseButton(const sf::Mouse::Button& sfButton)
{
    switch (sfButton)
    {
        case sf::Mouse::Button::Left:
        {
            return MouseButton::Left;
        }
        case sf::Mouse::Button::Right:
        {
            return MouseButton::Right;
        }
        default:
        {
            return MouseButton::None;
        }
    }
}

Key SfmlInputSource::translateToKeyData(const sf::Keyboard::Key& sfKey)
{
    switch (sfKey)
    {
        case sf::Keyboard::Key::Up:
        case sf::Keyboard::Key::W:
        {
            return Key::Up;
        }
        case sf::Keyboard::Key::Down:
        case sf::Keyboard::Key::S:
        {
            return Key::Down;
        }
        case sf::Keyboard::Key::Left:
        case sf::Keyboard::Key::A:
        {
            return Key::Left;
        }
        case sf::Keyboard::Key::Right:
        case sf::Keyboard::Key::D:
        {
            return Key::Right;
        }
        default:
        {
            return Key::None;
        }
    }
}
