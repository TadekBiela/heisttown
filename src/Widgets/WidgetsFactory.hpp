#pragma once

#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include <memory>

class WidgetsFactory
{
public:
    virtual ~WidgetsFactory() = default;

    virtual std::unique_ptr<Widget> create(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) const = 0;
};
