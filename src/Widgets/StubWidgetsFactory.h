#ifndef STUB_WIDGETS_FACTORY_H
#define STUB_WIDGETS_FACTORY_H

#include "StubWidget.h"
#include "Widget.h"
#include "WidgetGeometry.h"
#include "WidgetType.h"
#include "WidgetsFactory.h"
#include <memory>

class StubWidgetsFactory : public WidgetsFactory
{
public:
    StubWidgetsFactory() = default;
    virtual ~StubWidgetsFactory() = default;

    auto create(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) const -> std::unique_ptr<Widget> override
    {
        return std::make_unique<StubWidget>(type, geometry, text, style);
    }
};

#endif // STUB_WIDGETS_FACTORY_H
