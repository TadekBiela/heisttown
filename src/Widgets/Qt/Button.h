#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <Widget.h>
#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <memory>
#include <string>

class Button : public Widget
{
public:
    Button() = delete;
    Button(
        const WidgetGeometry& geometry,
        const std::string& text,
        const std::string& style
    );
    virtual ~Button() = default;

    virtual auto type() const -> WidgetType override;
    virtual auto geometry() const -> WidgetGeometry override;
    virtual void setGeometry(const WidgetGeometry& geometry) override;
    virtual auto text() const -> std::string override;
    virtual void setText(const std::string& text) override;
    virtual auto style() const -> std::string override;
    virtual void setStyle(const std::string& style) override;

private:
    std::unique_ptr<QPushButton> buttonImpl;
};

#endif // BUTTON_H
