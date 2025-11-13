#pragma once

#include "GameplayUpdate.hpp"
#include "GameSession.hpp"
#include <PlayerStatus.hpp>
#include <gmock/gmock.h>

class MockGameSession : public GameSession
{
public:
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD0(addPlayer, GameSession::PlayerID());
    MOCK_METHOD1(removePlayer, void(const PlayerID&));
    MOCK_METHOD2(queuePlayerStatus, void(const PlayerID&, const PlayerStatus&));
    MOCK_METHOD0(updateGameWorld, void());
    MOCK_CONST_METHOD1(getUpdateForPlayer, GameplayUpdate(const PlayerID&));
};
