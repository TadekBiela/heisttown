#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <Widget.h>
#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <memory>
#include <string>

class Label : public Widget
{
public:
    Label() = delete;
    Label(
        const WidgetGeometry& geometry,
        const std::string& text,
        const std::string& style
    );
    virtual ~Label() = default;

    virtual auto type() const -> WidgetType override;
    virtual auto geometry() const -> WidgetGeometry override;
    virtual void setGeometry(const WidgetGeometry& geometry) override;
    virtual auto text() const -> std::string override;
    virtual void setText(const std::string& text) override;
    virtual auto style() const -> std::string override;
    virtual void setStyle(const std::string& style) override;

private:
    std::unique_ptr<QLabel> labelImpl;
};

#endif // LABEL_H
