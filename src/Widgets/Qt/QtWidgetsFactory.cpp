#include "QtWidgetsFactory.h"
#include "Button.h"
#include "Label.h"

auto QtWidgetsFactory::create(
    const WidgetType& type,
    const WidgetGeometry& geometry,
    const WidgetText& text,
    const WidgetStyle& style
) const -> std::unique_ptr<Widget>
{
    switch (type)
    {
        case WidgetType::BUTTON:
            return std::make_unique<Button>(geometry, text, style);
        case WidgetType::LABEL:
            return std::make_unique<Label>(geometry, text, style);
    }

    return std::make_unique<Button>(geometry, text, style);
}
