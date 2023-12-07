#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <Widget.h>
#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <memory>

class Label : public Widget
{
public:
    Label() = delete;
    Label(
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    );
    virtual ~Label() = default;

    virtual auto type() const -> WidgetType override;
    virtual auto geometry() const -> WidgetGeometry override;
    virtual void setGeometry(const WidgetGeometry& geometry) override;
    virtual auto text() const -> WidgetText override;
    virtual void setText(const WidgetText& text) override;
    virtual auto style() const -> WidgetStyle override;
    virtual void setStyle(const WidgetStyle& style) override;

private:
    std::unique_ptr<QLabel> labelImpl;
};

#endif // LABEL_H
