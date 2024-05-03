#ifndef BUTTON_H
#define BUTTON_H

#include <ControlWidget.h>
#include <QMetaObject>
#include <QPushButton>
#include <QWidget>
#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <memory>

class Button : public ControlWidget
{
public:
    Button() = delete;
    Button(
        const std::shared_ptr<QWidget>& display,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    );
    virtual ~Button();

    auto type() const -> WidgetType override;
    auto geometry() const -> WidgetGeometry override;
    void setGeometry(const WidgetGeometry& geometry) override;
    auto text() const -> WidgetText override;
    void setText(const WidgetText& text) override;
    auto style() const -> WidgetStyle override;
    void setStyle(const WidgetStyle& style) override;
    void show() override;
    void hide() override;
    void connect(const ControlConnection& controlConnection) override;

protected:
    std::unique_ptr<QPushButton> buttonImpl;
    QMetaObject::Connection connection;
};

#endif // BUTTON_H
