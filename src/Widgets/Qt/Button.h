#ifndef BUTTON_H
#define BUTTON_H

#include <Widget.h>
#include <WidgetType.h>
#include <memory>

class QPushButton;

class Button : public Widget
{
public:
    Button();
    virtual ~Button() = default;

    virtual auto type() const->WidgetType override;
    virtual auto x() const->int override;
    virtual void setX(int x) override;
    virtual auto y() const->int override;
    virtual void setY(int y) override;
    virtual auto width() const->int override;
    virtual void setWidth(int width) override;
    virtual auto height() const->int override;
    virtual void setHeight(int height) override;
    virtual auto text() const->std::string override;
    virtual void setText(const std::string& text) override;
    virtual auto style() const->std::string override;
    virtual void setStyle(const std::string& style) override;

private:
    std::unique_ptr<QPushButton> buttonImpl;
    int _x{0};
    int _y{0};
    int _width{0};
    int _height{0};

    void updateGeometry();
};

#endif // BUTTON_H
