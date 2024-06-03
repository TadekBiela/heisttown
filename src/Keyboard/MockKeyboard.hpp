#ifndef MOCK_KEYBOARD_HPP
#define MOCK_KEYBOARD_HPP

#include "Keyboard.hpp"
#include <gmock/gmock.h>

class MockKeyboard : public Keyboard
{
public:
    MOCK_METHOD0(enable, void());
    MOCK_METHOD0(disable, void());
    MOCK_CONST_METHOD0(isEnabled, bool());
    MOCK_CONST_METHOD0(getPressedKey, char());
};

#endif // MOCK_KEYBOARD_HPP
