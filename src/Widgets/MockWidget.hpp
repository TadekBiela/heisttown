#pragma once

#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include <gmock/gmock.h>

class MockWidget : public Widget
{
public:
    MOCK_METHOD(WidgetType, getType, (), (const));
    MOCK_METHOD(WidgetGeometry, getGeometry, (), (const));
    MOCK_METHOD(void, setGeometry, (const WidgetGeometry& geometry));
    MOCK_METHOD(WidgetText, getText, (), (const));
    MOCK_METHOD(void, setText, (const WidgetText& text));
    MOCK_METHOD(WidgetStyle, getStyle, (), (const));
    MOCK_METHOD(void, setStyle, (const WidgetStyle& style));
    MOCK_METHOD(void, show, ());
    MOCK_METHOD(void, hide, ());
};
