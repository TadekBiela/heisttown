#pragma once

#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include <string>

using WidgetStyle = std::string;
using WidgetText = std::string;

class Widget
{
public:
    virtual ~Widget() = default;

    virtual WidgetType getType() const = 0;
    virtual WidgetGeometry getGeometry() const = 0;
    virtual void setGeometry(const WidgetGeometry& geometry) = 0;
    virtual WidgetText getText() const = 0;
    virtual void setText(const WidgetText& text) = 0;
    virtual WidgetStyle getStyle() const = 0;
    virtual void setStyle(const WidgetStyle& style) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};
