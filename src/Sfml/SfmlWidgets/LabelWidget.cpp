#include "LabelWidget.hpp"
#include <SFML/Graphics/Color.hpp>

LabelWidget::LabelWidget(
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

WidgetType LabelWidget::getType() const
{
    return WidgetType::LABEL;
}

void LabelWidget::applyStyle()
{
    applyStyleImpl();
}

void LabelWidget::applyStyleImpl()
{
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Transparent);
}
