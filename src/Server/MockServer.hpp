#pragma once

#include "Server.hpp"
#include <Client.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockServer : public Server
{
public:
    MOCK_METHOD1(setMainControl, void(const MainControlConnection&));
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD1(connect, void(std::shared_ptr<Client>));
};
