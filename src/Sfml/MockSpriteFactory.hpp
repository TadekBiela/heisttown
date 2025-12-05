#include "Sprite.hpp"
#include "SpriteFactory.hpp"
#include <SceneItem.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockSpriteFactory : public SpriteFactory
{
public:
    MockSpriteFactory()
        : SpriteFactory(nullptr)
    {}

    MOCK_METHOD(std::unique_ptr<Sprite>, create, (const SceneItemType&, const Position&, const Rotation&), (override));
};
