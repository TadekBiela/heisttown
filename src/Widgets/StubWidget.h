#ifndef STUB_WIDGET_H
#define STUB_WIDGET_H

#include "Widget.h"
#include "WidgetGeometry.h"
#include "WidgetType.h"

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

    auto type() const -> WidgetType;
    auto geometry() const -> WidgetGeometry;
    void setGeometry(const WidgetGeometry& geometry);
    auto text() const -> WidgetText;
    void setText(const WidgetText& text);
    auto style() const -> WidgetStyle;
    void setStyle(const WidgetStyle& style);
    void show();
    void hide();

private:
    WidgetType stubType;
    WidgetGeometry stubGeometry;
    WidgetText stubText;
    WidgetStyle stubStyle;
};

#endif // STUB_WIDGET_H
