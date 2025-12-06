#include "DisplaySfml.hpp"
#include <FilesStorage.hpp>
#include <MockFileLoader.hpp>
#include <SfmlRendering/MockSfmlRenderItem.hpp>
#include <SfmlRendering/MockSfmlRenderItemFactory.hpp>
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

    const SfmlRenderItems& getRenderItems() const
    {
        return renderItems;
    }
};

class DisplaySfmlTests : public Test
{
public:
    void SetUp() override
    {
        texture.create(1, 1);
    }

    [[nodiscard]] std::shared_ptr<FilesStorage<TextureFile>> createFileStorage() const
    {
        auto fileLoader { std::make_unique<MockFileLoader<TextureFile>>() };
        EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
        auto fileStorage { std::make_shared<FilesStorage<TextureFile>>(std::move(fileLoader)) };
        return fileStorage;
    }

    [[nodiscard]] std::unique_ptr<MockSfmlRenderItem> createMockSfmlRenderItem()
    {
        auto item { std::make_unique<MockSfmlRenderItem>(window, 0, texture, Position{ 0.0F, 0.0F }, 0.0F) };
        EXPECT_CALL(*item, getId()).Times(AtLeast(0)).WillRepeatedly(Return(0));
        return item;
    }

private:
    const std::map<FileName, TextureFile> data;
    sf::RenderWindow window;
    sf::Texture texture;
};

TEST_F(DisplaySfmlTests, update_EmptySceneUpdate_DoNothing)
{
    auto factory { std::make_unique<MockSfmlRenderItemFactory>() };
    EXPECT_CALL(*factory, create(SceneItemType::PLAYER, _, _)).Times(0);
    DisplaySfmlTestable display { 1, 1, createFileStorage(), std::move(factory) };

    display.update(SceneUpdate {});

    const auto& resultRenderItems { display.getDrawables() };
    EXPECT_TRUE(resultRenderItems.empty());
}

TEST_F(DisplaySfmlTests, update_SceneUpdateWithOneObject_AddOneItemToDrawables)
{
    SceneUpdate sceneUpdate;
    auto& sceneItems { sceneUpdate.sceneItems };
    sceneItems.push_back(SceneItem { 0, SceneItemType::PLAYER, { 0.0F, 0.0F }, 0.0F });
    auto factory { std::make_unique<MockSfmlRenderItemFactory>() };
    EXPECT_CALL(*factory, create(SceneItemType::PLAYER, _, _)).WillOnce(Return(ByMove(createMockSfmlRenderItem())));
    DisplaySfmlTestable display { 1, 1, createFileStorage(), std::move(factory) };

    display.update(sceneUpdate);

    const auto& resultRenderItems { display.getRenderItems() };
    EXPECT_EQ(1, resultRenderItems.size());
}

TEST_F(DisplaySfmlTests, update_SceneUpdateWithOneObjectUpdateTwice_AddOneItemToDrawablesAndUpdatePosition)
{
    SceneUpdate sceneUpdate;
    auto& sceneItems { sceneUpdate.sceneItems };
    sceneItems.push_back(SceneItem { 0, SceneItemType::PLAYER, { 0.0F, 0.0F }, 0.0F });
    const Position expectedPostion { 10.0F, 64.0F };
    auto factory { std::make_unique<MockSfmlRenderItemFactory>() };
    EXPECT_CALL(*factory, create(SceneItemType::PLAYER, _, _)).WillOnce(Return(ByMove(createMockSfmlRenderItem())));
    DisplaySfmlTestable display { 1, 1, createFileStorage(), std::move(factory) };

    display.update(sceneUpdate);
    sceneItems[0].position = { expectedPostion };
    display.update(sceneUpdate);

    const auto& resultRenderItems { display.getRenderItems() };
    ASSERT_EQ(1, resultRenderItems.size());
}
