#include "SceneItem.hpp"
#include "SceneItemFactory.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class SceneItemFactoryTestable : public SceneItemFactory
{
public:
    SceneItemId getNextSceneItemId() override
    {
        return notStaticIdCounter++;
    }

private:
    SceneItemId notStaticIdCounter { 0 };
};

class SceneItemFactoryTests : public Test
{
};

TEST_F(SceneItemFactoryTests, create_OneObject_ReturnCorrectSceneItem)
{
    const SceneItemType expectedType { SceneItemType::PLAYER };
    const Position expectedPosition { 40.5, 7.9 };
    const Rotation expectedRotation { 45.0 };
    SceneItemFactoryTestable factory;

    auto resutObject { factory.create(expectedType, expectedPosition, expectedRotation) };

    EXPECT_EQ(0, resutObject.id);
    EXPECT_EQ(expectedType, resutObject.type);
    EXPECT_EQ(expectedPosition, resutObject.position);
    EXPECT_EQ(expectedRotation, resutObject.rotation);
}

TEST_F(SceneItemFactoryTests, create_ThreeObjects_ReturnCreateSceneItemsWithDifferentId)
{
    SceneItemFactoryTestable factory;

    auto resutObject1 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resutObject2 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resutObject3 { factory.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resutObject1.id);
    EXPECT_EQ(1, resutObject2.id);
    EXPECT_EQ(2, resutObject3.id);
}

TEST_F(SceneItemFactoryTests, create_TwoFactoriesCreateOneObject_ReturnTwoObjectWithDifferentId)
{
    SceneItemFactory factory1;
    SceneItemFactory factory2;

    auto resutObject1 { factory1.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resutObject2 { factory2.create(SceneItemType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resutObject1.id);
    EXPECT_EQ(1, resutObject2.id);
}
