#pragma once

#include "Input.hpp"
#include <gmock/gmock.h>

class MockInput : public Input
{
public:
    MOCK_METHOD(void, setInputReceiver, (InputReceiver), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(PlayerStatus, getPlayerStatus, (), (const, override));
};
