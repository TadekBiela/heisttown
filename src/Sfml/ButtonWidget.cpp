#include "ButtonWidget.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

ButtonWidget::ButtonWidget(
    const WidgetGeometry& geometry,
    const WidgetText& text,
    const WidgetStyle& style,
    const std::shared_ptr<sf::Font>& font
)
    : DefaultWidgetImpl(
          geometry,
          text,
          style,
          font
      )
{
    applyStyleImpl();
}

void ButtonWidget::applyStyle()
{
    applyStyleImpl();
}

void ButtonWidget::applyStyleImpl()
{
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1.0);
}

WidgetType ButtonWidget::getType() const
{
    return WidgetType::BUTTON;
}

void ButtonWidget::connect(const ControlConnection& connection)
{
    controlConnection = connection;
}

bool ButtonWidget::handle(const sf::Event& event) const
{
    if (not visible)
    {
        return false;
    }

    if (event.type == sf::Event::EventType::MouseButtonPressed)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
        const auto mouseButton { event.mouseButton };
        if (mouseButton.button == sf::Mouse::Left)
        {
            const sf::Vector2f mousePosition(
                static_cast<float>(mouseButton.x),
                static_cast<float>(mouseButton.y)
            );

            if (shape.getGlobalBounds().contains(mousePosition))
            {
                controlConnection(DefaultWidgetImpl::getText());
                return true;
            }
        }
    }
    return false;
}
