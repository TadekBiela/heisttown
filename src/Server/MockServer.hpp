#pragma once

#include "Server.hpp"
#include <Client.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockServer : public Server
{
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, connect, (std::shared_ptr<Client>), (override));
    MOCK_METHOD(void, disconnect, (std::shared_ptr<Client>), (override));
};
