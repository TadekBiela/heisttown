#ifndef MOCK_DYNAMIC_WIDGET_H
#define MOCK_DYNAMIC_WIDGET_H

#include "DynamicWidget.h"
#include "MockWidget.h"

class MockDynamicWidget : public DynamicWidget, public MockWidget
{
public:
    MOCK_METHOD1(connect, void(ConnectionOutput output));
};

#endif // MOCK_DYNAMIC_WIDGET_H
