#pragma once

#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"
#include "WidgetsFactory.hpp"
#include <gmock/gmock.h>

class MockWidgetsFactory : public WidgetsFactory
{
public:
    MOCK_METHOD(std::shared_ptr<Widget>, create,
        (
            const WidgetType& type,
            const WidgetGeometry& geometry,
            const WidgetText& text,
            const WidgetStyle& style
        ),
        (override)
    );
};
