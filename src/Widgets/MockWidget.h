#ifndef MOCK_WIDGET_H
#define MOCK_WIDGET_H

#include "Widget.h"
#include "WidgetGeometry.h"
#include "WidgetType.h"
#include <gmock/gmock.h>

class MockWidget : public Widget
{
public:
    MOCK_CONST_METHOD0(type, WidgetType());
    MOCK_CONST_METHOD0(geometry, WidgetGeometry());
    MOCK_METHOD1(setGeometry, void(const WidgetGeometry& geometry));
    MOCK_CONST_METHOD0(text, WidgetText());
    MOCK_METHOD1(setText, void(const WidgetText& text));
    MOCK_CONST_METHOD0(style, WidgetStyle());
    MOCK_METHOD1(setStyle, void(const WidgetStyle& style));
    MOCK_METHOD0(show, void());
    MOCK_METHOD0(hide, void());
};

#endif // MOCK_WIDGET_H
