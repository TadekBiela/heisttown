#include "QtWidgetsFactory.h"
#include "Button.h"
#include <QPushButton>

auto QtWidgetsFactory::create(const WidgetType& type) const->std::unique_ptr<Widget>
{
    switch(type)
    {
        case WidgetType::BUTTON:
            return std::make_unique<Button>();
    }

    return std::make_unique<Button>();
}
