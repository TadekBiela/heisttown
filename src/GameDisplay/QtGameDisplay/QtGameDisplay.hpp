#ifndef QT_GAME_DISPLAY_HPP
#define QT_GAME_DISPLAY_HPP

#include <GameDisplay.hpp>
#include <QGraphicsView>
#include <memory>

class QtGameDisplay : public GameDisplay
{
public:
    QtGameDisplay(const std::shared_ptr<QWidget>& mainWindow);
    virtual ~QtGameDisplay() = default;

    void show() override;
    void hide() override;

private:
    std::unique_ptr<QGraphicsView> displayImpl;
};

#endif // QT_GAME_DISPLAY_HPP
