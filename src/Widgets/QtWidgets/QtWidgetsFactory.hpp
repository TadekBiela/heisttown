#ifndef QT_WIDGETS_FACTORY_HPP
#define QT_WIDGETS_FACTORY_HPP

#include <QWidget>
#include <Widget.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <WidgetsFactory.hpp>
#include <memory>

class QtWidgetsFactory : public WidgetsFactory
{
public:
    QtWidgetsFactory(std::shared_ptr<QWidget> display);
    virtual ~QtWidgetsFactory() = default;

    auto create(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) const -> std::unique_ptr<Widget> override;

private:
    std::shared_ptr<QWidget> widgetsDisplay;
};

#endif // QT_WIDGETS_FACTORY_HPP
