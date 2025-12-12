#pragma once

#include "GameplayUpdate.hpp"
#include "GameSession.hpp"
#include <PlayerStatus.hpp>
#include <gmock/gmock.h>

class MockGameSession : public GameSession
{
public:
    MockGameSession()
        : GameSession(nullptr)
    {}

    MOCK_METHOD(PlayerID, addPlayer, (), (override));
    MOCK_METHOD(void, removePlayer, (const PlayerID&), (override));
    MOCK_METHOD(void, queuePlayerStatus, (const PlayerID&, const PlayerStatus&), (override));
    MOCK_METHOD(void, updateGameWorld, (), (override));
    MOCK_METHOD(GameplayUpdate, getUpdateForPlayer, (const PlayerID&), (const, override));
};
