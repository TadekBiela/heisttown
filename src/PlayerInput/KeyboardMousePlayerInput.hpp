#ifndef KEYBOARD_MOUSE_PLAYER_INPUT_HPP
#define KEYBOARD_MOUSE_PLAYER_INPUT_HPP

#include "PlayerInput.hpp"
#include <Keyboard.hpp>
#include <memory>
#include <thread>

class KeyboardMousePlayerInput : public PlayerInput
{
public:
    KeyboardMousePlayerInput(std::unique_ptr<Keyboard> keyboard);
    virtual ~KeyboardMousePlayerInput();

    void setInputReceiver(PlayerInputReceiver inputReceiver) override;
    void start() override;
    void stop() override;

protected:
    PlayerInputReceiver playerInputReceiver { [](const PlayerInputCommand&){} };
    std::unique_ptr<Keyboard> inputKeyboard;
    std::thread keyboardReading;

private:
    void readKeyboard();
    void stopKeyboardReading();
};
#endif // KEYBOARD_MOUSE_PLAYER_INPUT_HPP
