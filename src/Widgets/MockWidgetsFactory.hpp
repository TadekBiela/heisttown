#pragma once

#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include "WidgetsFactory.hpp"
#include <gmock/gmock.h>

class MockWidgetsFactory : public WidgetsFactory
{
public:
    MOCK_CONST_METHOD4(
        create,
        std::unique_ptr<Widget>(
            const WidgetType& type,
            const WidgetGeometry& geometry,
            const WidgetText& text,
            const WidgetStyle& style
        )
    );
};
