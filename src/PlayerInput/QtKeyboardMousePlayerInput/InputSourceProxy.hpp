#ifndef INPUT_SOURCE_PROXY_HPP
#define INPUT_SOURCE_PROXY_HPP

#include <QEvent>
#include <QObject>
#include <functional>
#include <unordered_set>

enum class KeyState
{
    Pressed,
    Released
};

struct Key
{
    int value;
    KeyState state;
};

using KeyReceiver = std::function<void(Key)>;


class InputSourceProxy : public QObject
{
public:
    InputSourceProxy(KeyReceiver receiver);

protected:
    auto eventFilter(QObject* obj, QEvent* event) -> bool override;

private:
    KeyReceiver keyReceiver;
};

#endif // INPUT_SOURCE_PROXY_HPP
