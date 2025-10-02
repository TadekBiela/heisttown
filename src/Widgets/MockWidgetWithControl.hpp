#pragma once

#include "WidgetControl.hpp"
#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include <gmock/gmock.h>

class MockWidgetWithControl : public Widget, public WidgetControl
{
public:
    MOCK_CONST_METHOD0(getType, WidgetType());
    MOCK_CONST_METHOD0(getGeometry, WidgetGeometry());
    MOCK_METHOD1(setGeometry, void(const WidgetGeometry& geometry));
    MOCK_CONST_METHOD0(getText, WidgetText());
    MOCK_METHOD1(setText, void(const WidgetText& text));
    MOCK_CONST_METHOD0(getStyle, WidgetStyle());
    MOCK_METHOD1(setStyle, void(const WidgetStyle& style));
    MOCK_METHOD0(show, void());
    MOCK_METHOD0(hide, void());
    MOCK_METHOD1(connect, void(const ControlConnection& output));
};
