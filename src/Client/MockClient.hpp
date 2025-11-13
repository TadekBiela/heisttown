#pragma once

#include "Client.hpp"
#include <GameConnection.hpp>
#include <GameplayUpdate.hpp>
#include <PlayerInput.hpp>
#include <gmock/gmock.h>

class MockClient : public Client
{
public:
    MOCK_METHOD(void, connect, (const GameConnection&));
    MOCK_METHOD(void, start, ());
    MOCK_METHOD(void, stop, ());
    MOCK_METHOD(void, receive, (const PlayerInputCommand&));
    MOCK_METHOD(PlayerStatus, status, (), (const));
    MOCK_METHOD(void, update, (const GameplayUpdate&&));
};
