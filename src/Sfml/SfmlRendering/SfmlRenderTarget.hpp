#pragma once

#include <RenderTarget.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class SfmlRenderTarget : public RenderTarget
{
public:
    explicit SfmlRenderTarget(sf::RenderTarget& inputTarget);

    void render(const RenderItems& renderItems) override;
    sf::RenderTarget& getSfTarget();

private:
    sf::RenderTarget& target;
};
