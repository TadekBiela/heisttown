#include "WidgetsFactorySfml.hpp"
#include "ButtonWidget.hpp"
#include "LabelWidget.hpp"

WidgetsFactorySfml::WidgetsFactorySfml(const std::shared_ptr<sf::Font>& font, const std::shared_ptr<DisplaySfml>& displaySfml, const std::shared_ptr<InputDispatcher>& inputDispatcher)
    : widgetFont(font)
    , widgetDisplaySfml(displaySfml)
    , dispatcher(inputDispatcher)
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
            auto widget { std::make_shared<ButtonWidget>(geometry, text, style, widgetDisplaySfml->getRenderTarget(), widgetFont) };
            widgetDisplaySfml->add(widget);
            dispatcher->addHandler(widget);
            return widget;
        }
        case WidgetType::LABEL:
        {
            auto widget { std::make_shared<LabelWidget>(geometry, text, style, widgetDisplaySfml->getRenderTarget(), widgetFont) };
            widgetDisplaySfml->add(widget);
            return widget;
        }
        default:
        {
            return nullptr;
        }
    }
    return nullptr;
}
