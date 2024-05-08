#ifndef MOCK_CLIENT_HPP
#define MOCK_CLIENT_HPP

#include "Client.hpp"
#include <gmock/gmock.h>

class MockClient : public Client
{
public:
    MOCK_METHOD0(run, void());
};

#endif // MOCK_CLIENT_HPP
