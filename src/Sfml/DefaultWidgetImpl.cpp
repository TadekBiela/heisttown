#include "DefaultWidgetImpl.hpp"
#include <SFML/Graphics/Rect.hpp>

DefaultWidgetImpl::DefaultWidgetImpl(
    const WidgetGeometry& newGeometry,
    const WidgetText& newText,
    const WidgetStyle& newStyle,
    const std::shared_ptr<sf::Font>& newFont
)
    : geometry(newGeometry)
    , style(newStyle)
    , visible(false)
    , font(newFont)
{
    applyGeometry();
    applyText(newText);
    alignCenterText();
}

WidgetGeometry DefaultWidgetImpl::getGeometry() const
{
    return geometry;
}

void DefaultWidgetImpl::setGeometry(const WidgetGeometry& newGeometry)
{
    geometry = newGeometry;

    applyGeometry();
    alignCenterText();
}

void DefaultWidgetImpl::applyGeometry()
{
    shape.setPosition(
        geometry.x,
        geometry.y
    );
    shape.setSize({ geometry.width,
                    geometry.height });
}

WidgetText DefaultWidgetImpl::getText() const
{
    return textLabel.getString().toAnsiString();
}

void DefaultWidgetImpl::setText(const WidgetText& newText)
{
    applyText(newText);
    alignCenterText();
}

void DefaultWidgetImpl::applyText(const WidgetText& newText)
{
    textLabel.setFont(*font);
    textLabel.setString(newText);
}

void DefaultWidgetImpl::alignCenterText()
{
    const float centerDivider { 2.0 };
    const sf::FloatRect textBounds = textLabel.getLocalBounds();
    textLabel.setOrigin(
        textBounds.left + textBounds.width / centerDivider,
        textBounds.top + textBounds.height / centerDivider
    );
    textLabel.setPosition(
        geometry.x + geometry.width / centerDivider,
        geometry.y + geometry.height / centerDivider
    );
}

WidgetStyle DefaultWidgetImpl::getStyle() const
{
    return style;
}

void DefaultWidgetImpl::setStyle(const WidgetStyle& newStyle)
{
    style = newStyle;
    applyStyle();
}

void DefaultWidgetImpl::show()
{
    visible = true;
}

void DefaultWidgetImpl::hide()
{
    visible = false;
}

void DefaultWidgetImpl::draw(sf::RenderTarget& target) const
{
    if (not visible)
    {
        return;
    }

    target.draw(shape);
    target.draw(textLabel);
}
