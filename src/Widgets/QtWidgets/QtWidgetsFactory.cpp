#include "QtWidgetsFactory.hpp"
#include "Button.hpp"
#include "Label.hpp"

QtWidgetsFactory::QtWidgetsFactory(std::shared_ptr<QWidget> display)
    : widgetsDisplay(std::move(display))
{
}

auto QtWidgetsFactory::create(
    const WidgetType& type,
    const WidgetGeometry& geometry,
    const WidgetText& text,
    const WidgetStyle& style
) const -> std::unique_ptr<Widget>
{
    switch (type)
    {
        case WidgetType::LABEL:
            return std::make_unique<Label>(widgetsDisplay, geometry, text, style);
        case WidgetType::BUTTON:
        default:
            return std::make_unique<Button>(widgetsDisplay, geometry, text, style);
    }
}
