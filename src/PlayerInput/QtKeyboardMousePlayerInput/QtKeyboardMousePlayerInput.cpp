#include "QtKeyboardMousePlayerInput.hpp"
#include <iostream>

QtKeyboardMousePlayerInput::QtKeyboardMousePlayerInput(std::shared_ptr<QObject> source)
    : inputSource(std::move(source))
{
    keyReceiver = [&](Key key)
    {
        this->keyboardInput(key);
    };
}

QtKeyboardMousePlayerInput::~QtKeyboardMousePlayerInput()
{
    stopKeyboardReading();
}

void QtKeyboardMousePlayerInput::stopKeyboardReading()
{
    inputSource->removeEventFilter(getInputSourceProxy().get());
}

auto QtKeyboardMousePlayerInput::getInputSourceProxy() -> std::unique_ptr<InputSourceProxy>
{
    return std::make_unique<InputSourceProxy>(keyReceiver);
}

void QtKeyboardMousePlayerInput::setInputReceiver(PlayerInputReceiver inputReceiver)
{
    playerInputReceiver = std::move(inputReceiver);
}

void QtKeyboardMousePlayerInput::start()
{
    inputSource->installEventFilter(getInputSourceProxy().get());
}

void QtKeyboardMousePlayerInput::stop()
{
    stopKeyboardReading();
}

void QtKeyboardMousePlayerInput::keyboardInput(Key key)
{
    std::cout << "QtKeyboardMousePlayerInput::keyboardInput: key: "
              << key.value << ", " << (key.state == KeyState::Pressed ? 0 : 1) << std::endl;
    if (key.value == Qt::Key_Escape) // 27 == ESC
    {
        playerInputReceiver("Keyboard: ESC");
    }
}
