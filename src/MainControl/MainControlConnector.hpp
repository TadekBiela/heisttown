#pragma once

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
