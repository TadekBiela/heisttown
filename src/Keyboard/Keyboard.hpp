#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

class Keyboard
{
public:
    virtual ~Keyboard() = default;

    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual auto isEnabled() const -> bool = 0;
    virtual auto getPressedKey() const -> char = 0;
};

#endif // KEYBOARD_HPP
