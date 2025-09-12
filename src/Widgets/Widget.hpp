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

    virtual auto getType() const -> WidgetType = 0;
    virtual auto getGeometry() const -> WidgetGeometry = 0;
    virtual void setGeometry(const WidgetGeometry& geometry) = 0;
    virtual auto getText() const -> WidgetText = 0;
    virtual void setText(const WidgetText& text) = 0;
    virtual auto getStyle() const -> WidgetStyle = 0;
    virtual void setStyle(const WidgetStyle& style) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};
