#ifndef MAIN_APPLICATION_HPP
#define MAIN_APPLICATION_HPP

#include <MenuController.hpp>

class MainApplication
{
public:
    virtual ~MainApplication() = default;

    virtual void control(const MainCommand& command) = 0;
};

#endif // MAIN_APPLICATION_HPP
