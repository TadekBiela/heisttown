#pragma once

#include <variant>

enum class InputEventType
{
    MouseMove,
    MouseButtonPressed,
    MouseButtonReleased,
    KeyPressed,
    Quit
};

struct MouseMoveData
{
    float x;
    float y;
};

struct MouseButtonData
{
    int button;
};

struct KeyData
{
    int key;
};

struct InputEvent
{
    InputEventType type;
    std::variant<MouseMoveData, MouseButtonData, KeyData, std::monostate> data;
};

