#pragma once

#include <string>

struct WidgetGeometry
{
    float x { 0.0 };
    float y { 0.0 };
    float width { 0.0 };
    float height { 0.0 };

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
