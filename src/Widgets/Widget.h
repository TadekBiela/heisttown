#ifndef WIDGETS_H
#define WIDGETS_H

#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <string>

using WidgetStyle = std::string;
using WidgetText = std::string;

class Widget
{
public:
    virtual ~Widget() = default;

    virtual auto type() const -> WidgetType = 0;
    virtual auto geometry() const -> WidgetGeometry = 0;
    virtual void setGeometry(const WidgetGeometry& geometry) = 0;
    virtual auto text() const -> WidgetText = 0;
    virtual void setText(const WidgetText& text) = 0;
    virtual auto style() const -> WidgetStyle = 0;
    virtual void setStyle(const WidgetStyle& style) = 0;
};

#endif // WIDGETS_H
