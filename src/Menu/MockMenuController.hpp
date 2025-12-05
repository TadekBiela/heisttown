#pragma once

#include "IMenuController.hpp"
#include <WidgetControl.hpp>
#include <gmock/gmock.h>

class MockMenuController : public IMenuController
{
public:
    MOCK_METHOD(void, handle, (const WidgetCommand&), (override));
    MOCK_METHOD(void, connect, (const MenuConnection&), (override));
    MOCK_METHOD(void, showMenu, (), (override));
};
