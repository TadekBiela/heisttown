#include "WidgetsFactorySfml.hpp"
#include "ButtonWidget.hpp"
#include "LabelWidget.hpp"

WidgetsFactorySfml::WidgetsFactorySfml(
    const std::shared_ptr<sf::Font>& font,
    const std::shared_ptr<SfmlWindow>& sfmlWindow,
    const std::shared_ptr<InputDispatcher>& inputDispatcher
)
    : widgetFont(font)
    , widgetSfmlWindow(sfmlWindow)
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
            auto widget { std::make_shared<ButtonWidget>(geometry, text, style, widgetSfmlWindow->getRenderTarget(), widgetFont) };
            widgetSfmlWindow->add(widget);
            dispatcher->addHandler(widget);
            return widget;
        }
        case WidgetType::LABEL:
        {
            auto widget { std::make_shared<LabelWidget>(geometry, text, style, widgetSfmlWindow->getRenderTarget(), widgetFont) };
            widgetSfmlWindow->add(widget);
            return widget;
        }
        default:
        {
            return nullptr;
        }
    }
    return nullptr;
}
