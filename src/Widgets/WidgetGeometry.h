#ifndef WIDGET_GEOMETRY_H
#define WIDGET_GEOMETRY_H

struct WidgetGeometry
{
    const int x;
    const int y;
    const int width;
    const int height;

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
