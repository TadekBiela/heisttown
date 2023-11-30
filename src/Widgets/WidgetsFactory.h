#ifndef WIDGETS_FACTORY_H
#define WIDGETS_FACTORY_H

#include <WidgetType.h>
#include <memory>

class Widget;

class WidgetsFactory
{
public:
    virtual ~WidgetsFactory() = default;

    virtual auto create(const WidgetType& type) const->std::unique_ptr<Widget> = 0;
};

#endif // WIDGETS_FACTORY_H
