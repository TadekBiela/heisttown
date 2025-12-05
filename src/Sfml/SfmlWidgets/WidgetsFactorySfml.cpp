#include "WidgetsFactorySfml.hpp"
#include "ButtonWidget.hpp"
#include "LabelWidget.hpp"

WidgetsFactorySfml::WidgetsFactorySfml(
    const std::shared_ptr<sf::Font>& font,
    const std::shared_ptr<DisplaySfml>& displaySfml
)
    : widgetFont(font)
    , widgetDisplaySfml(displaySfml)
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
            widgetDisplaySfml->addDrawable(widget);
            widgetDisplaySfml->addEventHandler(widget);
            return widget;
        }
        case WidgetType::LABEL:
        {
            auto widget { std::make_shared<LabelWidget>(geometry, text, style, widgetFont) };
            widgetDisplaySfml->addDrawable(widget);
            return widget;
        }
        default:
        {
            return nullptr;
        }
    }
    return nullptr;
}
