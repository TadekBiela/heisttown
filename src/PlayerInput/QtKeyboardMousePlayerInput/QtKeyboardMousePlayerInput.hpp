#ifndef KEYBOARD_MOUSE_PLAYER_INPUT_HPP
#define KEYBOARD_MOUSE_PLAYER_INPUT_HPP

#include "InputSourceProxy.hpp"
#include <PlayerInput.hpp>
#include <QObject>
#include <memory>

class QtKeyboardMousePlayerInput : public PlayerInput
{
public:
    QtKeyboardMousePlayerInput(std::shared_ptr<QObject> source);
    virtual ~QtKeyboardMousePlayerInput();

    void setInputReceiver(PlayerInputReceiver inputReceiver) override;
    void start() override;
    void stop() override;

private:
    PlayerInputReceiver playerInputReceiver { [](const PlayerInputCommand&){} };
    std::shared_ptr<QObject> inputSource;
    KeyReceiver keyReceiver;
    std::unique_ptr<InputSourceProxy> proxy;

    void keyboardInput(Key key);
    void stopKeyboardReading();
};
#endif // KEYBOARD_MOUSE_PLAYER_INPUT_HPP
