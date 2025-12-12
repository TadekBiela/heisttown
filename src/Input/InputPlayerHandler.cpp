#include "InputPlayerHandler.hpp"
#include <iostream>

InputPlayerHandler::InputPlayerHandler()
    : isUpPressed(false)
    , isDownPressed(false)
    , isLeftPressed(false)
    , isRightPressed(false)
{
}

bool InputPlayerHandler::handle(const InputEvent& event)
{
    // std::cerr << __func__ << " event: " << static_cast<unsigned>(event.type) << "\n";
    switch (event.type)
    {
        case InputEventType::KeyPressed:
        {
            if (const auto* keyData = std::get_if<KeyData>(&event.data))
            {
                switch (keyData->key)
                {
                    case Key::Up:
                    {
                        isUpPressed = true;
                        break;
                    }
                    case Key::Down:
                    {
                        isDownPressed = true;
                        break;
                    }
                    case Key::Left:
                    {
                        isLeftPressed = true;
                        break;
                    }
                    case Key::Right:
                    {
                        isRightPressed = true;
                        break;
                    }
                    case Key::None:
                    {
                        return false;
                    }
                }
            }
            break;
        }
        case InputEventType::KeyReleased:
        {
            if (const auto* keyData = std::get_if<KeyData>(&event.data))
            {
                switch (keyData->key)
                {
                    case Key::Up:
                    {
                        isUpPressed = false;
                        break;
                    }
                    case Key::Down:
                    {
                        isDownPressed = false;
                        break;
                    }
                    case Key::Left:
                    {
                        isLeftPressed = false;
                        break;
                    }
                    case Key::Right:
                    {
                        isRightPressed = false;
                        break;
                    }
                    case Key::None:
                    {
                        return false;
                    }
                }
            }
            break;
        }
        default:
            return false;
    }

    if (isUpPressed)
    {
        playerStatus.moveDirection = Direction::FRONT;
        if (isRightPressed)
        {
            playerStatus.moveDirection = Direction::FRONT_RIGHT;
        }
        else if (isLeftPressed)
        {
            playerStatus.moveDirection = Direction::FRONT_LEFT;
        }
    }
    else if (isDownPressed)
    {
        playerStatus.moveDirection = Direction::BACK;
        if (isRightPressed)
        {
            playerStatus.moveDirection = Direction::BACK_RIGHT;
        }
        else if (isLeftPressed)
        {
            playerStatus.moveDirection = Direction::BACK_LEFT;
        }
    }
    else if (isRightPressed)
    {
        playerStatus.moveDirection = Direction::RIGHT;
    }
    else if (isLeftPressed)
    {
        playerStatus.moveDirection = Direction::LEFT;
    }

    playerStatus.moveVelocity = (isUpPressed or isDownPressed or isLeftPressed or isRightPressed) ? 1.0F : 0.0F;
    return true;
}

void InputPlayerHandler::setInputReceiver(InputReceiver inputReceiver)
{
    inputCommandReceiver = std::move(inputReceiver);
}

PlayerStatus InputPlayerHandler::getPlayerStatus() const
{
    return playerStatus;
}
