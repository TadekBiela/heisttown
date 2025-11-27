#include "Sprite.hpp"
#include "SpriteFactory.hpp"
#include <GameObject.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockSpriteFactory : public SpriteFactory
{
public:
    MockSpriteFactory()
        : SpriteFactory(nullptr)
    {}

    MOCK_METHOD(std::unique_ptr<Sprite>, create, (const GoType&, const Position&, const Rotation&));
};
