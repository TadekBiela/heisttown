#ifndef WIDGETS_FACTORY_H
#define WIDGETS_FACTORY_H

#include <Widget.h>
#include <WidgetGeometry.h>
#include <WidgetType.h>
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

#endif // WIDGETS_FACTORY_H
