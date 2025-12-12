#include "SfmlRenderSceneBuilder.hpp"
#include <FilesStorage.hpp>
#include <MockFileLoader.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SceneUpdate.hpp>
#include <gtest/gtest.h>
#include <map>
#include <memory>

using namespace testing;

class SfmlRenderSceneBuilderTestable : public SfmlRenderSceneBuilder
{
public:
    using SfmlRenderSceneBuilder::SfmlRenderSceneBuilder;

    const sf::Texture& getLocalMapTexture() const
    {
        return localMapTexture;
    }

    const RenderItems& getRenderItems() const
    {
        return renderItems;
    }

    SceneItemId getItemIdCounter() const
    {
        return itemIdCounter;
    }
};

class SfmlRenderSceneBuilderTests : public Test
{
public:
    SfmlRenderSceneBuilderTests()
        : window(sf::VideoMode(100, 100), "", sf::Style::None)
    {
        data["map01"] = SfmlTextureFile();
        data["player"] = SfmlTextureFile();
    }

    sf::RenderWindow& getWindow()
    {
        return window;
    }

    [[nodiscard]] std::unique_ptr<FilesStorage<SfmlTextureFile>> createFileStorage() const
    {
        auto fileLoader { std::make_unique<MockFileLoader<SfmlTextureFile>>() };
        EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
        auto fileStorage { std::make_unique<FilesStorage<SfmlTextureFile>>(std::move(fileLoader)) };
        return fileStorage;
    }

private:
    sf::RenderWindow window;
    std::map<FileName, SfmlTextureFile> data;
};

TEST_F(SfmlRenderSceneBuilderTests, constructor_InputWindowWithSize_LocalMapWithSameSizeAsWindow)
{
    const SfmlRenderSceneBuilderTestable builder { getWindow(), createFileStorage() };

    const auto& resultMapTexture { builder.getLocalMapTexture() };
    EXPECT_EQ(getWindow().getSize(), resultMapTexture.getSize());
}

TEST_F(SfmlRenderSceneBuilderTests, build_EmptySceneUpdate_DoNothing)
{
    SfmlRenderSceneBuilderTestable builder { getWindow(), createFileStorage() };

    builder.build(SceneUpdate {});

    const auto& resultRenderItems { builder.getRenderItems() };
    EXPECT_TRUE(resultRenderItems.empty());
}

TEST_F(SfmlRenderSceneBuilderTests, build_SceneUpdateWithOnlyMapName_LoadGlobalAndLocalMapAndAddPlayerRenderItem)
{
    const Position expectedPlayerPosition { 50.0F, 50.0F };
    SceneUpdate update;
    update.mapName = "map01";
    SfmlRenderSceneBuilderTestable builder { getWindow(), createFileStorage() };

    builder.build(update);

    const auto& resultRenderItems { builder.getRenderItems() };
    ASSERT_EQ(2, resultRenderItems.size()); // Map and Player
    const auto* resultPlayerItem { dynamic_cast<SfmlRenderItem*>(resultRenderItems.at(1).get()) };
    ASSERT_FALSE(resultPlayerItem == nullptr);
    EXPECT_FLOAT_EQ(expectedPlayerPosition.x, resultPlayerItem->getPosition().x);
    EXPECT_FLOAT_EQ(expectedPlayerPosition.y, resultPlayerItem->getPosition().y);
}

TEST_F(SfmlRenderSceneBuilderTests, popRenderItems_TwoRenderItems_ReturnTwoRenderItemsClearInsideRenderITemsAndResetIdCounter)
{
    SceneUpdate update;
    update.mapName = "map01";
    SfmlRenderSceneBuilderTestable builder { getWindow(), createFileStorage() };
    builder.build(update);

    const auto resultRenderItems { builder.popRenderItems() };

    EXPECT_EQ(2, resultRenderItems.size());
    EXPECT_EQ(0, builder.getRenderItems().size());
    EXPECT_EQ(1, builder.getItemIdCounter());
}
