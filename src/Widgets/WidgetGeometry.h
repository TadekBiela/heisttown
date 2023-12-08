#ifndef WIDGET_GEOMETRY_H
#define WIDGET_GEOMETRY_H

struct WidgetGeometry
{
    const int x { 0 };
    const int y { 0 };
    const int width { 0 };
    const int height { 0 };

    bool operator==(const WidgetGeometry& geometry) const
    {
        return (
            this->x == geometry.x &&
            this->y == geometry.y &&
            this->width == geometry.width &&
            this->height == geometry.height
        );
    }
};

#endif // WIDGET_GEOMETRY_H
