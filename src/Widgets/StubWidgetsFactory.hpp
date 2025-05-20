#pragma once

#include "StubWidget.hpp"
#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include "WidgetsFactory.hpp"
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
