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

    MOCK_METHOD(void, start, ());
    MOCK_METHOD(void, stop, ());
    MOCK_METHOD(PlayerID, addPlayer, ());
    MOCK_METHOD(void, removePlayer, (const PlayerID&));
    MOCK_METHOD(void, queuePlayerStatus, (const PlayerID&, const PlayerStatus&));
    MOCK_METHOD(void, updateGameWorld, ());
    MOCK_METHOD(GameplayUpdate, getUpdateForPlayer, (const PlayerID&), (const));
};
