#include "InputDispatcher.hpp"

InputDispatcher::InputDispatcher(std::shared_ptr<InputSource> source)
    : inputSource(std::move(source))
{
}

void InputDispatcher::addHandler(const std::shared_ptr<InputHandler>& handler)
{
    handlers.push_back(handler);
}

void InputDispatcher::dispatch()
{
    auto events = inputSource->pollEvents();

    for (const auto& event : events)
    {
        for (auto& handler : handlers)
        {
            if (handler->handle(event))
            {
                break;
            }
        }
    }
}
