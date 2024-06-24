#ifndef MAIN_CONTROL_CONNECTOR_HPP
#define MAIN_CONTROL_CONNECTOR_HPP

#include <functional>
#include <string>

using MainCommand = std::string;
using MainControlConnection = std::function<void(const MainCommand&)>;

class MainControlConnector
{
public:
    virtual ~MainControlConnector() = default;

    virtual void setMainControl(const MainControlConnection& controlConnection) = 0;
};

#endif // MAIN_CONTROL_CONNECTOR_HPP
