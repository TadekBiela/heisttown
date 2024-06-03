#include "KeyboardMousePlayerInput.hpp"
#include <chrono>
#include <iostream>

KeyboardMousePlayerInput::KeyboardMousePlayerInput(std::unique_ptr<Keyboard> keyboard)
    : inputKeyboard(std::move(keyboard))
{
}

KeyboardMousePlayerInput::~KeyboardMousePlayerInput()
{
    stopKeyboardReading();
}

void KeyboardMousePlayerInput::stopKeyboardReading()
{
    inputKeyboard->disable();
    if (keyboardReading.joinable())
    {
        keyboardReading.join();
    }
}

void KeyboardMousePlayerInput::setInputReceiver(PlayerInputReceiver inputReceiver)
{
    playerInputReceiver = std::move(inputReceiver);
}

void KeyboardMousePlayerInput::start()
{
    if (!keyboardReading.joinable())
    {
        inputKeyboard->enable();
        keyboardReading = std::thread(
            [&]()
            {
                readKeyboard();
            }
        );
    }
}

void KeyboardMousePlayerInput::stop()
{
    stopKeyboardReading();
}

void KeyboardMousePlayerInput::readKeyboard()
{
    while (inputKeyboard->isEnabled())
    {
        auto key = inputKeyboard->getPressedKey();
        std::cerr << "Pressed key: " << key << std::endl;
        if (key == 27) // 27 == ESC key
        {
            playerInputReceiver("Keyboard: ESC");
            inputKeyboard->disable();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
