#ifndef MOCK_MENU_CONTROLLER_HPP
#define MOCK_MENU_CONTROLLER_HPP

#include "IMenuController.hpp"
#include <gmock/gmock.h>

class MockMenuController : public IMenuController
{
public:
    MOCK_METHOD1(control, void(const WidgetCommand& command));
    MOCK_METHOD1(setMainControl, void(const MainControlConnection& mainControlConnection));
};

#endif // MOCK_MENU_CONTROLLER_HPP
