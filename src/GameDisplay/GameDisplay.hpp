#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

class GameDisplay
{
public:
    virtual ~GameDisplay() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
};

#endif // GAME_DISPLAY_HPP
