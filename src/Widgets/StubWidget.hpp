#ifndef STUB_WIDGET_HPP
#define STUB_WIDGET_HPP

#include "Widget.hpp"
#include "WidgetGeometry.hpp"
#include "WidgetType.hpp"

class StubWidget : public Widget
{
public:
    StubWidget() = default;
    StubWidget(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        WidgetText text,
        WidgetStyle style
    );
    virtual ~StubWidget() = default;

    auto type() const -> WidgetType override;
    auto geometry() const -> WidgetGeometry override;
    void setGeometry(const WidgetGeometry& geometry) override;
    auto text() const -> WidgetText override;
    void setText(const WidgetText& text) override;
    auto style() const -> WidgetStyle override;
    void setStyle(const WidgetStyle& style) override;
    void show() override;
    void hide() override;

private:
    WidgetType stubType;
    WidgetGeometry stubGeometry;
    WidgetText stubText;
    WidgetStyle stubStyle;
};

#endif // STUB_WIDGET_HPP
