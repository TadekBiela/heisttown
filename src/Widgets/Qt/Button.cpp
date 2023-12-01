#include "Button.h"
#include <QPushButton>

Button::Button()
    : buttonImpl(std::make_unique<QPushButton>())
{
}

auto Button::type() const->WidgetType
{
    return WidgetType::BUTTON;
}

auto Button::x() const->int
{
    return buttonImpl->x();
}

void Button::setX(int x)
{
    _x = x;
    updateGeometry();
}

void Button::updateGeometry()
{
    buttonImpl->setGeometry(_x, _y, _width, _height);
}

auto Button::y() const->int
{
    return buttonImpl->y();
}

void Button::setY(int y)
{
    _y = y;
    updateGeometry();
}

auto Button::width() const->int
{
    return buttonImpl->width();
}

void Button::setWidth(int width)
{
    _width = width;
    updateGeometry();
}

auto Button::height() const->int
{
    return buttonImpl->height();
}

void Button::setHeight(int height)
{
    _height = height;
    updateGeometry();
}

auto Button::text() const->std::string
{
    return buttonImpl->text().toStdString();
}

void Button::setText(const std::string& text)
{
    buttonImpl->setText(text.c_str());
}

auto Button::style() const->std::string
{
    return buttonImpl->styleSheet().toStdString();
}

void Button::setStyle(const std::string& style)
{
    buttonImpl->setStyleSheet(style.c_str());
}
