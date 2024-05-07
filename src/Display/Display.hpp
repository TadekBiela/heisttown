#ifndef DISPLAY_HPP
#define DISPLAY_HPP

class Display
{
public:
    virtual ~Display() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
};

#endif // DISPLAY_HPP
