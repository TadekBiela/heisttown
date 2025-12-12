#pragma once

#include "InputEvent.hpp"
#include "InputHandler.hpp"
#include "PlayerStatus.hpp"
#include <functional>
#include <string>

using InputCommand = std::string;
using InputReceiver = std::function<void(const InputCommand&)>;

class InputPlayerHandler : public InputHandler
{
public:
    InputPlayerHandler();
    virtual ~InputPlayerHandler() override = default;

    virtual bool handle(const InputEvent& event) override;
    virtual void setInputReceiver(InputReceiver inputReceiver);
    [[nodiscard]] virtual PlayerStatus getPlayerStatus() const;

private:
    InputReceiver inputCommandReceiver;
    PlayerStatus playerStatus;
    bool isUpPressed;
    bool isDownPressed;
    bool isLeftPressed;
    bool isRightPressed;

    static bool isMoveKey(const Key& key);
};
