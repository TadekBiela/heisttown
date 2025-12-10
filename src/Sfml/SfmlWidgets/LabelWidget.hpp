#pragma once

#include "DefaultWidgetImpl.hpp"
#include <Widget.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

class LabelWidget : public DefaultWidgetImpl
{
public:
    LabelWidget(
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style,
        sf::RenderTarget& target,
        const std::shared_ptr<sf::Font>& font = nullptr
    );

    [[nodiscard]] WidgetType getType() const override;

private:
    void applyStyle() override;
    void applyStyleImpl();
};
