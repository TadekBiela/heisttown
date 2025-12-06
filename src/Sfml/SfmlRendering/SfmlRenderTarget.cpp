#include "SfmlRenderTarget.hpp"
#include <SFML/Graphics/Drawable.hpp>

SfmlRenderTarget::SfmlRenderTarget(sf::RenderTarget& inputTarget)
    : target(inputTarget)
{
}

void SfmlRenderTarget::render(const RenderItems& renderItems)
{
    for (const auto& item : renderItems)
    {
        item->render();
    }
}

sf::RenderTarget& SfmlRenderTarget::getSfTarget()
{
    return target;
}
