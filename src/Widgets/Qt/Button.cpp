#include "Button.h"

Button::Button(
    const WidgetGeometry& geometry,
    const WidgetText& text,
    const WidgetStyle& style
)
    : buttonImpl(std::make_unique<QPushButton>())
{
    buttonImpl->setGeometry(
        geometry.x,
        geometry.y,
        geometry.width,
        geometry.height
    );
    buttonImpl->setText(text.c_str());
    buttonImpl->setStyleSheet(style.c_str());
}

auto Button::type() const -> WidgetType
{
    return WidgetType::BUTTON;
}

auto Button::geometry() const -> WidgetGeometry
{
    return WidgetGeometry {
        buttonImpl->x(),
        buttonImpl->y(),
        buttonImpl->width(),
        buttonImpl->height()
    };
}

void Button::setGeometry(const WidgetGeometry& geometry)
{
    buttonImpl->setGeometry(
        geometry.x,
        geometry.y,
        geometry.width,
        geometry.height
    );
}

auto Button::text() const -> WidgetText
{
    return buttonImpl->text().toStdString();
}

void Button::setText(const WidgetText& text)
{
    buttonImpl->setText(text.c_str());
}

auto Button::style() const -> WidgetStyle
{
    return buttonImpl->styleSheet().toStdString();
}

void Button::setStyle(const WidgetStyle& style)
{
    buttonImpl->setStyleSheet(style.c_str());
}
