#pragma once

#include "IMenuController.hpp"
#include <WidgetControl.hpp>
#include <gmock/gmock.h>

class MockMenuController : public IMenuController
{
public:
    MOCK_METHOD(void, handle, (const WidgetCommand&));
    MOCK_METHOD(void, connect, (const MenuConnection&));
    MOCK_METHOD(void, showMenu, ());
};
