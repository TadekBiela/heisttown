#ifndef WIDGET_GEOMETRY_H
#define WIDGET_GEOMETRY_H

#include <string>

struct WidgetGeometry
{
    int x { 0 };
    int y { 0 };
    int width { 0 };
    int height { 0 };

    bool operator==(const WidgetGeometry& geometry) const
    {
        return (
            this->x == geometry.x &&
            this->y == geometry.y &&
            this->width == geometry.width &&
            this->height == geometry.height
        );
    }

    std::string toString() const
    {
        return std::string(
            std::to_string(x) + ", " +
            std::to_string(y) + ", " +
            std::to_string(width) + ", " +
            std::to_string(height)
        );
    }
};

#endif // WIDGET_GEOMETRY_H
