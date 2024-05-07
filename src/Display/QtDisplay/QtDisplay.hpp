#ifndef QT_DISPLAY_HPP
#define QT_DISPLAY_HPP

#include <Display.hpp>
#include <QGraphicsView>
#include <memory>

class QtDisplay : public Display
{
public:
    QtDisplay(const std::shared_ptr<QWidget>& mainWindow);
    virtual ~QtDisplay() = default;

private:
    std::unique_ptr<QGraphicsView> displayImpl;
};

#endif // QT_DISPLAY_HPP
