#include "StubWidget.hpp"

StubWidget::StubWidget(
    const WidgetType& type,
    const WidgetGeometry& geometry,
    WidgetText text,
    WidgetStyle style
)
    : stubType(type)
    , stubGeometry(geometry)
    , stubText(std::move(text))
    , stubStyle(std::move(style))
{
}

auto StubWidget::type() const -> WidgetType
{
    return stubType;
}

auto StubWidget::geometry() const -> WidgetGeometry
{
    return stubGeometry;
}

void StubWidget::setGeometry(const WidgetGeometry& geometry)
{
    stubGeometry = geometry;
}

auto StubWidget::text() const -> WidgetText
{
    return stubText;
}

void StubWidget::setText(const WidgetText& text)
{
    stubText = text;
}

auto StubWidget::style() const -> WidgetStyle
{
    return stubStyle;
}

void StubWidget::setStyle(const WidgetStyle& style)
{
    stubStyle = style;
}

void StubWidget::show()
{
}

void StubWidget::hide()
{
}
