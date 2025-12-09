#pragma once

#include "Client.hpp"
#include <GameConnection.hpp>
#include <GameplayUpdate.hpp>
#include <Input.hpp>
#include <gmock/gmock.h>

class MockClient : public Client
{
public:
    MOCK_METHOD(void, connect, (const GameConnection&), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, receive, (const InputCommand&), (override));
    MOCK_METHOD(PlayerStatus, status, (), (const, override));
    MOCK_METHOD(void, update, (const GameplayUpdate&&), (override));
};
