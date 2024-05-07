#include "QtDisplay.hpp"

QtDisplay::QtDisplay(const std::shared_ptr<QWidget>& mainWindow)
    : displayImpl(std::make_unique<QGraphicsView>(mainWindow.get()))
{
    displayImpl->showFullScreen();
}
