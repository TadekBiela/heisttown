#include "ButtonWidget.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <variant>

ButtonWidget::ButtonWidget(
    const WidgetGeometry& geometry,
    const WidgetText& text,
    const WidgetStyle& style,
    sf::RenderTarget& target,
    const std::shared_ptr<sf::Font>& font
)
    : DefaultWidgetImpl(
          geometry,
          text,
          style,
          target,
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

bool ButtonWidget::handle(const InputEvent& event)
{
    if (not visible)
    {
        return false;
    }

    if (event.type == InputEventType::MouseButtonPressed)
    {
        const auto* mouseButton = std::get_if<MouseButtonData>(&event.data);
        if (mouseButton->button == MouseButton::Left)
        {
            const sf::Vector2f mousePosition { mouseButton->x, mouseButton->y };

            if (shape.getGlobalBounds().contains(mousePosition))
            {
                controlConnection(DefaultWidgetImpl::getText());
                return true;
            }
        }
    }

    return false;
}
