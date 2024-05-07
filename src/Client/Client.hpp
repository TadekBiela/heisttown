#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client
{
public:
    virtual ~Client() = default;

    virtual void run() = 0;
};

#endif // CLIENT_HPP
