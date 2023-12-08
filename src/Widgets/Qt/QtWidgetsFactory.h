#ifndef QT_WIDGETS_FACTORY_H
#define QT_WIDGETS_FACTORY_H

#include <Widget.h>
#include <WidgetGeometry.h>
#include <WidgetsFactory.h>
#include <WidgetType.h>
#include <memory>

class QtWidgetsFactory : public WidgetsFactory
{
public:
    QtWidgetsFactory() = default;
    virtual ~QtWidgetsFactory() = default;

    virtual auto create(
        const WidgetType& type,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) const -> std::unique_ptr<Widget> override;
};

#endif // QT_WIDGETS_FACTORY_H
