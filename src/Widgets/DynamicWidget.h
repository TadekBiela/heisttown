#ifndef DYNAMIC_WIDGET_H
#define DYNAMIC_WIDGET_H

#include "Widget.h"
#include <functional>
#include <string>

using WidgetMessage = std::string;
using ConnectionOutput = std::function<void(const WidgetMessage&)>;

class DynamicWidget : public Widget
{
public:
    virtual ~DynamicWidget() = default;

    virtual void connect(const ConnectionOutput& output) = 0;
};

#endif // DYNAMIC_WIDGET_H
