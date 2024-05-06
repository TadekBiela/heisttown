#ifndef LABEL_HPP
#define LABEL_HPP

#include <QLabel>
#include <QWidget>
#include <Widget.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <memory>

class Label : public Widget
{
public:
    Label() = delete;
    Label(
        const std::shared_ptr<QWidget>& display,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    );
    virtual ~Label() = default;

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
    std::unique_ptr<QLabel> labelImpl;
};

#endif // LABEL_HPP
