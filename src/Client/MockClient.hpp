#ifndef MOCK_CLIENT_HPP
#define MOCK_CLIENT_HPP

#include "Client.hpp"
#include <PlayerInput.hpp>
#include <gmock/gmock.h>

class MockClient : public Client
{
public:
    MOCK_METHOD0(startSinglePlayerGame, void());
    MOCK_METHOD1(receive, void(const PlayerInputCommand&));
};

#endif // MOCK_CLIENT_HPP
