#pragma once

#include "Client.hpp"
#include <PlayerInput.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockClient : public Client
{
public:
    MOCK_METHOD1(connect, void(const GameConnection&));
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD1(receive, void(const PlayerInputCommand&));
    MOCK_CONST_METHOD0(status, PlayerStatus());
    MOCK_METHOD1(update, void(std::unique_ptr<GameplayUpdate>));
};
