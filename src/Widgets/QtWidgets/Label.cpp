#include "Label.hpp"

Label::Label(
    const std::shared_ptr<QWidget>& display,
    const WidgetGeometry& geometry,
    const WidgetText& text,
    const WidgetStyle& style
)
    : labelImpl(std::make_unique<QLabel>())
{
    labelImpl->setParent(display.get());
    labelImpl->setGeometry(
        geometry.x,
        geometry.y,
        geometry.width,
        geometry.height
    );
    labelImpl->setText(text.c_str());
    labelImpl->setStyleSheet(style.c_str());
}

auto Label::type() const -> WidgetType
{
    return WidgetType::LABEL;
}

auto Label::geometry() const -> WidgetGeometry
{
    return WidgetGeometry {
        labelImpl->x(),
        labelImpl->y(),
        labelImpl->width(),
        labelImpl->height()
    };
}

void Label::setGeometry(const WidgetGeometry& geometry)
{
    labelImpl->setGeometry(
        geometry.x,
        geometry.y,
        geometry.width,
        geometry.height
    );
}

auto Label::text() const -> WidgetText
{
    return labelImpl->text().toStdString();
}

void Label::setText(const WidgetText& text)
{
    labelImpl->setText(text.c_str());
}

auto Label::style() const -> WidgetStyle
{
    return labelImpl->styleSheet().toStdString();
}

void Label::setStyle(const WidgetStyle& style)
{
    labelImpl->setStyleSheet(style.c_str());
}

void Label::show()
{
    labelImpl->show();
}

void Label::hide()
{
    labelImpl->hide();
}
