#include "SfmlRenderItemFactory.hpp"
#include "TextureFile.hpp"
#include <FilesStorage.hpp>
#include <MockFileLoader.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SceneItem.hpp>
#include <SfmlRenderItem.hpp>
#include <gtest/gtest.h>

using namespace testing;

class SfmlRenderItemFactoryTestable : public SfmlRenderItemFactory
{
public:
    using SfmlRenderItemFactory::SfmlRenderItemFactory;

private:
    SceneItemId getNextSceneItemId() override
    {
        return id++;
    }

    SceneItemId id { 0 };
};

class SfmlRenderItemFactoryTests : public Test
{
};

TEST_F(SfmlRenderItemFactoryTests, create_OneSfmlRenderItem_ReturnSfmlRenderItem)
{
    sf::RenderWindow target;
    const std::map<FileName, TextureFile> data;
    auto fileLoader { std::make_unique<MockFileLoader<TextureFile>>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
    auto fileStorage { std::make_shared<FilesStorage<TextureFile>>(std::move(fileLoader)) };
    SfmlRenderItemFactoryTestable factory { target, fileStorage };

    auto resultSfmlRenderItem { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resultSfmlRenderItem->getId());
}

TEST_F(SfmlRenderItemFactoryTests, create_ThreeSfmlRenderItems_ReturnSfmlRenderItemsWithDifferentId)
{
    sf::RenderWindow target;
    const std::map<FileName, TextureFile> data;
    auto fileLoader { std::make_unique<MockFileLoader<TextureFile>>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
    auto fileStorage { std::make_shared<FilesStorage<TextureFile>>(std::move(fileLoader)) };
    SfmlRenderItemFactoryTestable factory { target, fileStorage };

    auto resultSfmlRenderItem1 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resultSfmlRenderItem2 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resultSfmlRenderItem3 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resultSfmlRenderItem1->getId());
    EXPECT_EQ(1, resultSfmlRenderItem2->getId());
    EXPECT_EQ(2, resultSfmlRenderItem3->getId());
}

TEST_F(SfmlRenderItemFactoryTests, create_ToFactoriesCreateOneSfmlRenderItem_ReturnSfmlRenderItemsWithDifferentId)
{
    sf::RenderWindow target;
    const std::map<FileName, TextureFile> data;
    auto fileLoader { std::make_unique<MockFileLoader<TextureFile>>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
    auto fileStorage { std::make_shared<FilesStorage<TextureFile>>(std::move(fileLoader)) };
    SfmlRenderItemFactory factory1 { target, fileStorage };
    SfmlRenderItemFactory factory2 { target, fileStorage };

    auto resultSfmlRenderItem1 { factory1.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resultSfmlRenderItem2 { factory2.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resultSfmlRenderItem1->getId());
    EXPECT_EQ(1, resultSfmlRenderItem2->getId());
}
