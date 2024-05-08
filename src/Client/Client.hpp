#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client
{
public:
    virtual ~Client() = default;

    virtual void startSinglePlayerGame() = 0;
};

#endif // CLIENT_HPP
