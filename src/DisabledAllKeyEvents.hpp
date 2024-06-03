#ifndef DISABLED_ALL_KEY_EVENTS_HPP
#define DISABLED_ALL_KEY_EVENTS_HPP

#include <QEvent>
#include <QObject>

class DisabledAllKeyEvents : public QObject
{
    Q_OBJECT

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
    }
};

#endif // DISABLED_ALL_KEY_EVENTS_HPP
