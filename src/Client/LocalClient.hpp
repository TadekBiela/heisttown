#ifndef LOCAL_CLIENT_HPP
#define LOCAL_CLIENT_HPP

#include "Client.hpp"
#include <Display.hpp>
#include <memory>

class LocalClient : public Client
{
public:
    LocalClient(std::unique_ptr<Display> display);
    virtual ~LocalClient() = default;

    void run() override;

private:
    std::unique_ptr<Display> gameDisplay;
};

#endif // LOCAL_CLIENT_HPP
