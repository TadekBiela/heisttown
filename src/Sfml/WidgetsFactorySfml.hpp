#pragma once

#include "EventDispatcher.hpp"
#include "Renderer.hpp"
#include <Widget.hpp>
#include <WidgetsFactory.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

class WidgetsFactorySfml : public WidgetsFactory
{
public:
    explicit WidgetsFactorySfml(
        const std::shared_ptr<sf::Font>& font,
        const std::shared_ptr<Renderer>& renderer,
        const std::shared_ptr<EventDispatcher>& eventDispatcher
    );

    std::shared_ptr<Widget> create(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) override;

private:
    std::shared_ptr<sf::Font> widgetFont;
    std::shared_ptr<Renderer> widgetRenderer;
    std::shared_ptr<EventDispatcher> widgetEventDispatcher;
};
