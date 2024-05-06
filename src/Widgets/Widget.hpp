#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
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
    virtual void show() = 0;
    virtual void hide() = 0;
};

#endif // WIDGET_HPP
