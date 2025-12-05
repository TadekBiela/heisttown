#include "DisplaySfml.hpp"
#include "MockSprite.hpp"
#include "MockSpriteFactory.hpp"
#include <FilesStorage.hpp>
#include <MockFileLoader.hpp>
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
public:
    [[nodiscard]] std::shared_ptr<FilesStorage<TextureFile>> createFileStorage() const
    {
        auto fileLoader { std::make_unique<MockFileLoader<TextureFile>>() };
        EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
        auto fileStorage { std::make_shared<FilesStorage<TextureFile>>(std::move(fileLoader)) };
        return fileStorage;
    }

    [[nodiscard]] static std::unique_ptr<MockSprite> createMockSprite()
    {
        auto sprite { std::make_unique<MockSprite>() };
        EXPECT_CALL(*sprite, getId()).Times(AtLeast(0)).WillRepeatedly(Return(0));
        return sprite;
    }

private:
    const std::map<FileName, TextureFile> data;
};

TEST_F(DisplaySfmlTests, update_EmptySceneUpdate_DoNothing)
{
    auto spriteFactory { std::make_unique<MockSpriteFactory>() };
    EXPECT_CALL(*spriteFactory, create(SceneItemType::PLAYER, _, _)).Times(0);
    DisplaySfmlTestable display { 1, 1, createFileStorage(), std::move(spriteFactory) };

    display.update(SceneUpdate {});

    const auto& resultSprites { display.getDrawables() };
    EXPECT_TRUE(resultSprites.empty());
}

TEST_F(DisplaySfmlTests, update_SceneUpdateWithOneObject_AddOneSpriteToDrawables)
{
    SceneUpdate sceneUpdate;
    auto& sceneItems { sceneUpdate.sceneItems };
    sceneItems.push_back(SceneItem { 0, SceneItemType::PLAYER, { 0.0F, 0.0F }, 0.0F });
    auto spriteFactory { std::make_unique<MockSpriteFactory>() };
    EXPECT_CALL(*spriteFactory, create(SceneItemType::PLAYER, _, _)).WillOnce(Return(ByMove(createMockSprite())));
    DisplaySfmlTestable display { 1, 1, createFileStorage(), std::move(spriteFactory) };

    display.update(sceneUpdate);

    const auto& resultSprites { display.getSprites() };
    EXPECT_EQ(1, resultSprites.size());
}

TEST_F(DisplaySfmlTests, update_SceneUpdateWithOneObjectUpdateTwice_AddOneSpriteToDrawablesAndUpdatePosition)
{
    SceneUpdate sceneUpdate;
    auto& sceneItems { sceneUpdate.sceneItems };
    sceneItems.push_back(SceneItem { 0, SceneItemType::PLAYER, { 0.0F, 0.0F }, 0.0F });
    const Position expectedPostion { 10.0F, 64.0F };
    auto spriteFactory { std::make_unique<MockSpriteFactory>() };
    EXPECT_CALL(*spriteFactory, create(SceneItemType::PLAYER, _, _)).WillOnce(Return(ByMove(createMockSprite())));
    DisplaySfmlTestable display { 1, 1, createFileStorage(), std::move(spriteFactory) };

    display.update(sceneUpdate);
    sceneItems[0].position = { expectedPostion };
    display.update(sceneUpdate);

    const auto& resultSprites { display.getSprites() };
    ASSERT_EQ(1, resultSprites.size());
}
