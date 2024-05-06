#ifndef WIDGETS_FACTORY_HPP
#define WIDGETS_FACTORY_HPP

#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include <memory>

class WidgetsFactory
{
public:
    virtual ~WidgetsFactory() = default;

    virtual auto create(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) const -> std::unique_ptr<Widget> = 0;
};

#endif // WIDGETS_FACTORY_HPP
