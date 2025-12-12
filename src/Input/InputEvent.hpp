#pragma once

#include <cstdint>
#include <variant>

enum class InputEventType : std::uint8_t
{
    MouseMove,
    MouseButtonPressed,
    MouseButtonReleased,
    KeyPressed,
    KeyReleased,
    Quit,
    NotSupported
};

struct MouseMoveData
{
    float x;
    float y;
};

enum class MouseButton : std::uint8_t
{
    Left,
    Right,
    None
};

struct MouseButtonData
{
    MouseButton button;
    float x;
    float y;
};

enum class Key : std::uint8_t
{
    Up,
    Down,
    Left,
    Right,
    None
};

struct KeyData
{
    Key key;
};

struct InputEvent
{
    InputEventType type { InputEventType::NotSupported };
    std::variant<MouseMoveData, MouseButtonData, KeyData, std::monostate> data;
};

