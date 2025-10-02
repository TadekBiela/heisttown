#include "WidgetsFactorySfml.hpp"
#include "ButtonWidget.hpp"
#include "LabelWidget.hpp"

WidgetsFactorySfml::WidgetsFactorySfml(
    const std::shared_ptr<sf::Font>& font,
    const std::shared_ptr<Renderer>& renderer,
    const std::shared_ptr<EventDispatcher>& eventDispatcher
)
    : widgetFont(font)
    , widgetRenderer(renderer)
    , widgetEventDispatcher(eventDispatcher)
{
}

std::shared_ptr<Widget> WidgetsFactorySfml::create(
    const WidgetType& type,
    const WidgetGeometry& geometry,
    const WidgetText& text,
    const WidgetStyle& style
)
{
    switch (type)
    {
        case WidgetType::BUTTON:
        {
            auto widget { std::make_shared<ButtonWidget>(geometry, text, style, widgetFont) };
            widgetRenderer->addDrawable(widget);
            widgetEventDispatcher->addEventHandler(widget);
            return widget;
        }
        case WidgetType::LABEL:
        {
            auto widget { std::make_shared<LabelWidget>(geometry, text, style, widgetFont) };
            widgetRenderer->addDrawable(widget);
            return widget;
        }
        default:
        {
            return nullptr;
        }
    }
    return nullptr;
}
