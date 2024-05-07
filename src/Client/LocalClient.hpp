#ifndef LOCAL_CLIENT_HPP
#define LOCAL_CLIENT_HPP

#include "Client.hpp"

class LocalClient : public Client
{
public:
    LocalClient() = default;
    virtual ~LocalClient() = default;

    void run() override;
};

#endif // LOCAL_CLIENT_HPP
