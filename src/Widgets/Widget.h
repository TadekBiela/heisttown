#ifndef WIDGETS_H
#define WIDGETS_H

#include <WidgetType.h>
#include <string>

class Widget
{
public:
    virtual ~Widget() = default;

    virtual auto type() const->WidgetType = 0;
    virtual auto x() const->int = 0;
    virtual void setX(int x) = 0;
    virtual auto y() const->int  = 0;
    virtual void setY(int y) = 0;
    virtual auto width() const->int  = 0;
    virtual void setWidth(int width) = 0;
    virtual auto height() const->int  = 0;
    virtual void setHeight(int height) = 0;
    virtual auto text() const->std::string = 0;
    virtual void setText(const std::string& text) = 0;
    virtual auto style() const->std::string = 0;
    virtual void setStyle(const std::string& style) = 0;
};

#endif // WIDGETS_H
