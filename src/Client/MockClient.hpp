#pragma once

#include "Client.hpp"
#include <PlayerInput.hpp>
#include <gmock/gmock.h>

class MockClient : public Client
{
public:
    MOCK_METHOD1(connect, void(const GameConnection&));
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD1(receive, void(const PlayerInputCommand&));
};
