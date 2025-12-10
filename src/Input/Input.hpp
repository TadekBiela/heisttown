#pragma once

#include "PlayerStatus.hpp"
#include <functional>
#include <string>

using InputCommand = std::string;
using InputReceiver = std::function<void(const InputCommand&)>;

class Input
{
public:
    virtual ~Input() = default;

    virtual void setInputReceiver(InputReceiver inputReceiver) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    [[nodiscard]] virtual PlayerStatus getPlayerStatus() const = 0;
};
