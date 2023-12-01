#ifndef WIDGETS_FACTORY_H
#define WIDGETS_FACTORY_H

#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <memory>
#include <string>

class Widget;

class WidgetsFactory
{
public:
    virtual ~WidgetsFactory() = default;

    virtual auto create(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        const std::string& text,
        const std::string& style
    ) const -> std::unique_ptr<Widget> = 0;
};

#endif // WIDGETS_FACTORY_H
