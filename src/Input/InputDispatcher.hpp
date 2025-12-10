#pragma once

#include "InputSource.hpp"
#include "InputHandler.hpp"
#include <vector>
#include <memory>

class InputDispatcher
{
public:
    using InputHandlers = std::vector<std::shared_ptr<InputHandler>>;

    explicit InputDispatcher(std::shared_ptr<InputSource> source);
    virtual ~InputDispatcher() = default;

    virtual void addHandler(const std::shared_ptr<InputHandler>& handler);
    virtual void dispatch();

protected:
    InputHandlers handlers;

private:
    std::shared_ptr<InputSource> inputSource;
};
