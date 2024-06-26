#ifndef MOCK_MENU_CONTROLLER_HPP
#define MOCK_MENU_CONTROLLER_HPP

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

#endif // MOCK_MENU_CONTROLLER_HPP
