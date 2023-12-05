#include "Label.h"

Label::Label(
    const WidgetGeometry& geometry,
    const std::string& text,
    const std::string& style
)
    : labelImpl(std::make_unique<QLabel>())
{
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

auto Label::text() const -> std::string
{
    return labelImpl->text().toStdString();
}

void Label::setText(const std::string& text)
{
    labelImpl->setText(text.c_str());
}

auto Label::style() const -> std::string
{
    return labelImpl->styleSheet().toStdString();
}

void Label::setStyle(const std::string& style)
{
    labelImpl->setStyleSheet(style.c_str());
}
