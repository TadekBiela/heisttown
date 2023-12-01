#ifndef WIDGETS_H
#define WIDGETS_H

#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <string>

class Widget
{
public:
    virtual ~Widget() = default;

    virtual auto type() const -> WidgetType = 0;
    virtual auto geometry() const -> WidgetGeometry = 0;
    virtual void setGeometry(const WidgetGeometry& geometry) = 0;
    virtual auto text() const -> std::string = 0;
    virtual void setText(const std::string& text) = 0;
    virtual auto style() const -> std::string = 0;
    virtual void setStyle(const std::string& style) = 0;
};

#endif // WIDGETS_H
