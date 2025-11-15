#include "DisplaySfml.hpp"
#include "MockSprite.hpp"
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
};

class DisplaySfmlTests : public Test
{
};

TEST_F(DisplaySfmlTests, update_EmptyGameSceneUpdate_DoNothing)
{
    DisplaySfmlTestable display { 1, 1 };

    display.update(GameSceneUpdate {});

    const auto& resultDrawables { display.getDrawables() };
    EXPECT_TRUE(resultDrawables.empty());
}

TEST_F(DisplaySfmlTests, update_GameSceneUpdateWithOneObject_AddOneSpriteToDrawables)
{
    GameSceneUpdate sceneUpdate;
    auto& gameObjects { sceneUpdate.gameObjects };
    gameObjects.push_back(GameObject { 0, GoType::PLAYER, { 0, 0 }, 0 });
    DisplaySfmlTestable display { 1, 1 };

    display.update(sceneUpdate);

    const auto& resultDrawables { display.getDrawables() };
    EXPECT_EQ(1, resultDrawables.size());
}
