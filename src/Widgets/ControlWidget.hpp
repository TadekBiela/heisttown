#pragma once

#include "Widget.hpp"
#include <functional>
#include <string>

using WidgetCommand = std::string;
using ControlConnection = std::function<void(const WidgetCommand&)>;

class ControlWidget : public Widget
{
public:
    virtual ~ControlWidget() = default;

    virtual void connect(const ControlConnection& controlConnection) = 0;
};
