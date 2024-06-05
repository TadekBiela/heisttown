#include "InputSourceProxy.hpp"
#include <QKeyEvent>

InputSourceProxy::InputSourceProxy(KeyReceiver receiver)
    : keyReceiver(std::move(receiver))
{
}

auto InputSourceProxy::eventFilter(QObject* obj, QEvent* event) -> bool
{
    if (event->type() == QEvent::KeyPress)
    {
        auto* keyEvent = dynamic_cast<QKeyEvent*>(event);
        keyReceiver({ keyEvent->key(), KeyState::Pressed });
        return true;
    }
    return QObject::eventFilter(obj, event);
}
