#pragma once

#include <GraphicsStorage>
#include <memory>

class SpriteFactory
{
public:
    SpriteFactory(std::shared_ptr<GraphicsStorage> inputGraphicsStorage);

private:
    std::shared_ptr<GraphicsStorage> graphicsStorage;
};
