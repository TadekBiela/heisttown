#pragma once

#include "IMenuController.hpp"
#include <ControlWidget.hpp>
#include <gmock/gmock.h>

class MockMenuController : public IMenuController
{
public:
    MOCK_METHOD1(handle, void(const WidgetCommand&));
    MOCK_METHOD1(connect, void(const MenuConnection&));
    MOCK_METHOD0(showMenu, void());
};
