#pragma once

#include "IMenuController.hpp"
#include <MainControlConnector.hpp>
#include <gmock/gmock.h>

class MockMenuController : public IMenuController
{
public:
    MOCK_METHOD1(setMainControl, void(const MainControlConnection&));
    MOCK_METHOD1(control, void(const WidgetCommand& command));
    MOCK_METHOD0(showMenu, void());
};
