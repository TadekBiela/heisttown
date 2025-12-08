#include "DisplaySfml.hpp"
#include <FilesStorage.hpp>
#include <MockFileLoader.hpp>
#include <MockRenderSceneBuilder.hpp>
#include <SfmlRendering/SfmlTextureFile.hpp>
#include <gtest/gtest.h>
#include <map>
#include <memory>

using namespace testing;

class DisplaySfmlTests : public Test
{
public:
    [[nodiscard]] std::unique_ptr<FilesStorage<SfmlTextureFile>> createFileStorage() const
    {
        auto fileLoader { std::make_unique<MockFileLoader<SfmlTextureFile>>() };
        EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(data));
        auto fileStorage { std::make_unique<FilesStorage<SfmlTextureFile>>(std::move(fileLoader)) };
        return fileStorage;
    }

private:
    const std::map<FileName, SfmlTextureFile> data;
};

TEST_F(DisplaySfmlTests, update_EmptySceneUpdate_BuildSceneViaSceneBuilder)
{
    auto sceneBuilder { std::make_unique<MockRenderSceneBuilder>() };
    EXPECT_CALL(*sceneBuilder, build(_));
    DisplaySfml display { 1, 1, createFileStorage(), std::move(sceneBuilder) };

    display.update(SceneUpdate {});
}
