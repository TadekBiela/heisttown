#pragma once

#include "../Drawable.hpp"
#include <Widget.hpp>
#include <WidgetGeometry.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>

class DefaultWidgetImpl : public Widget, public Drawable
{
public:
    DefaultWidgetImpl(
        const WidgetGeometry& newGeometry,
        const WidgetText& newText,
        const WidgetStyle& newStyle,
        const std::shared_ptr<sf::Font>& newFont = nullptr
    );

    [[nodiscard]] WidgetGeometry getGeometry() const  override;
    void setGeometry(const WidgetGeometry& newGeometry) override;
    [[nodiscard]] WidgetText getText() const override;
    void setText(const WidgetText& newText) override;
    [[nodiscard]] WidgetStyle getStyle() const override;
    void setStyle(const WidgetStyle& newStyle) override;
    void show() override;
    void hide() override;
    void draw(sf::RenderTarget& target) const override;

protected:
    WidgetGeometry geometry;
    WidgetStyle style;
    bool visible;
    sf::RectangleShape shape;
    sf::Text textLabel;
    std::shared_ptr<sf::Font> font;

    void applyGeometry();
    void applyText(const WidgetText& newText);
    void alignCenterText();
    virtual void applyStyle() = 0;
};
