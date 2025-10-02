#pragma once

#include <functional>
#include <string>

using WidgetCommand = std::string;
using ControlConnection = std::function<void(const WidgetCommand&)>;

class WidgetControl
{
public:
    virtual ~WidgetControl() = default;

    virtual void connect(const ControlConnection& controlConnection) = 0;
};
