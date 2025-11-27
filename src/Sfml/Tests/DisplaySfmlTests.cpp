#include "DisplaySfml.hpp"
#include "MockSprite.hpp"
#include "MockSpriteFactory.hpp"
#include <gtest/gtest.h>

using namespace testing;

class DisplaySfmlTestable : public DisplaySfml
{
public:
    using DisplaySfml::DisplaySfml;

    const Drawables& getDrawables() const
    {
        return drawables;
    }

    const Sprites& getSprites() const
    {
        return sprites;
    }
};

class DisplaySfmlTests : public Test
{
};

TEST_F(DisplaySfmlTests, update_EmptyGameSceneUpdate_DoNothing)
{
    auto spriteFactory { std::make_unique<MockSpriteFactory>() };
    DisplaySfmlTestable display { 1, 1, std::move(spriteFactory) };

    display.update(GameSceneUpdate {});

    const auto& resultSprites { display.getDrawables() };
    EXPECT_TRUE(resultSprites.empty());
}

TEST_F(DisplaySfmlTests, update_GameSceneUpdateWithOneObject_AddOneSpriteToDrawables)
{
    GameSceneUpdate sceneUpdate;
    auto& gameObjects { sceneUpdate.gameObjects };
    gameObjects.push_back(GameObject { 0, GoType::PLAYER, { 0, 0 }, 0 });
    auto sprite { std::make_unique<MockSprite>() };
    EXPECT_CALL(*sprite, getId()).WillOnce(Return(0));
    auto spriteFactory { std::make_unique<MockSpriteFactory>() };
    EXPECT_CALL(*spriteFactory, create(GoType::PLAYER, _, _)).WillOnce(Return(ByMove(std::move(sprite))));
    DisplaySfmlTestable display { 1, 1, std::move(spriteFactory) };

    display.update(sceneUpdate);

    const auto& resultSprites { display.getSprites() };
    EXPECT_EQ(1, resultSprites.size());
}

TEST_F(DisplaySfmlTests, update_GameSceneUpdateWithOneObjectUpdateTwice_AddOneSpriteToDrawablesAndUpdatePosition)
{
    GameSceneUpdate sceneUpdate;
    auto& gameObjects { sceneUpdate.gameObjects };
    gameObjects.push_back(GameObject { 0, GoType::PLAYER, { 0, 0 }, 0 });
    const Position expectedPostion { 10.0, 64.0 };
    auto sprite { std::make_unique<MockSprite>() };
    EXPECT_CALL(*sprite, getId()).WillOnce(Return(0));
    auto spriteFactory { std::make_unique<MockSpriteFactory>() };
    EXPECT_CALL(*spriteFactory, create(GoType::PLAYER, _, _)).WillOnce(Return(ByMove(std::move(sprite))));
    DisplaySfmlTestable display { 1, 1, std::move(spriteFactory) };

    display.update(sceneUpdate);
    gameObjects[0].position = { expectedPostion };
    display.update(sceneUpdate);

    const auto& resultSprites { display.getSprites() };
    ASSERT_EQ(1, resultSprites.size());
}
