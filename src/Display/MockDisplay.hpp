#pragma once

#include "Display.hpp"
#include "Displayable.hpp"
#include <gmock/gmock.h>
#include <memory>

class MockDisplay : public Display
{
public:
    MOCK_METHOD1(add, void(std::weak_ptr<Displayable>));
    MOCK_METHOD0(show, void());
    MOCK_METHOD0(hide, void());
};
