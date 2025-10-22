#pragma once

#include "Display.hpp"
#include <gmock/gmock.h>

class MockDisplay : public Display
{
public:
    MOCK_METHOD0(show, void());
    MOCK_METHOD0(hide, void());
};
