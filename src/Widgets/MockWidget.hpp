#pragma once

#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include <gmock/gmock.h>

class MockWidget : public Widget
{
public:
    MOCK_METHOD(WidgetType, getType, (), (const, override));
    MOCK_METHOD(WidgetGeometry, getGeometry, (), (const, override));
    MOCK_METHOD(void, setGeometry, (const WidgetGeometry& geometry), (override));
    MOCK_METHOD(WidgetText, getText, (), (const, override));
    MOCK_METHOD(void, setText, (const WidgetText& text), (override));
    MOCK_METHOD(WidgetStyle, getStyle, (), (const, override));
    MOCK_METHOD(void, setStyle, (const WidgetStyle& style), (override));
    MOCK_METHOD(void, show, (), (override));
    MOCK_METHOD(void, hide, (), (override));
};
