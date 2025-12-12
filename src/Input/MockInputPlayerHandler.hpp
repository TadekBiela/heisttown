#pragma once

#include "InputEvent.hpp"
#include "InputPlayerHandler.hpp"
#include "PlayerStatus.hpp"
#include <gmock/gmock.h>

class MockInputPlayerHandler : public InputPlayerHandler
{
public:
    MOCK_METHOD(bool, handle, (const InputEvent& event), (override));
    MOCK_METHOD(void, setInputReceiver, (InputReceiver inputReceiver), (override));
    MOCK_METHOD(PlayerStatus, getPlayerStatus, (), (const, override));
};
