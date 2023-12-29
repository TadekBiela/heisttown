#include "Widget.h"
#include "WidgetGeometry.h"
#include "WidgetType.h"
#include "WidgetsFactory.h"
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
