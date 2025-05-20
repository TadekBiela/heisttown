#pragma once

#include "GameDisplay.hpp"
#include <gmock/gmock.h>

class MockGameDisplay : public GameDisplay
{
public:
    MOCK_METHOD0(show, void());
    MOCK_METHOD0(hide, void());
};
