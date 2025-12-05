#include "SpriteFactory.hpp"
#include "TextureFile.hpp"
#include <FilesStorage.hpp>
#include <MockFileLoader.hpp>
#include <SceneItem.hpp>
#include <Sprite.hpp>
#include <gtest/gtest.h>

using namespace testing;

class SpriteFactoryTests : public Test
{
};

TEST_F(SpriteFactoryTests, create_OneSprite_ReturnSprite)
{
    const std::map<FileName, TextureFile> data;
    auto fileLoader { std::make_unique<MockFileLoader<TextureFile>>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
    auto fileStorage { std::make_shared<FilesStorage<TextureFile>>(std::move(fileLoader)) };
    SpriteFactory factory { fileStorage };

    auto resultSprite { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resultSprite->getId());
}

TEST_F(SpriteFactoryTests, create_ThreeSprites_ReturnSpritesWithDifferentId)
{
    const std::map<FileName, TextureFile> data;
    auto fileLoader { std::make_unique<MockFileLoader<TextureFile>>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
    auto fileStorage { std::make_shared<FilesStorage<TextureFile>>(std::move(fileLoader)) };
    SpriteFactory factory { fileStorage };

    auto resultSprite1 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resultSprite2 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resultSprite3 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resultSprite1->getId());
    EXPECT_EQ(1, resultSprite2->getId());
    EXPECT_EQ(2, resultSprite3->getId());
}
