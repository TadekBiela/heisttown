#pragma once

#include "DefaultWidgetImpl.hpp"
#include "../EventHandler.hpp"
#include <WidgetControl.hpp>
#include <Widget.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

class ButtonWidget : public WidgetControl, public DefaultWidgetImpl, public EventHandler
{
public:
    ButtonWidget(
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style,
        const std::shared_ptr<sf::Font>& font = nullptr
    );

    [[nodiscard]] WidgetType getType() const override;
    void connect(const ControlConnection& connection) override;
    bool handle(const sf::Event& event) const override;

protected:
    ControlConnection controlConnection;

private:
    void applyStyle() override;
    void applyStyleImpl();
};
