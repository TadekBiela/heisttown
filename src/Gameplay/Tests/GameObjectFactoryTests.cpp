#include "GameSession.hpp"
#include "GameObjectFactory.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class GameObjectFactoryTestable : public GameObjectFactory
{
public:
    GoId getNextGoId() override
    {
        return notStaticIdCounter++;
    }

private:
    GoId notStaticIdCounter { 0 };
};

class GameObjectFactoryTests : public Test
{
};

TEST_F(GameObjectFactoryTests, create_OneObject_ReturnCorrectGameObject)
{
    const GoType expectedType { GoType::PLAYER };
    const Position expectedPosition { 40.5, 7.9 };
    const Rotation expectedRotation { 45.0 };
    GameObjectFactoryTestable factory;

    auto resutObject { factory.create(expectedType, expectedPosition, expectedRotation) };

    EXPECT_EQ(0, resutObject.id);
    EXPECT_EQ(expectedType, resutObject.type);
    EXPECT_EQ(expectedPosition, resutObject.position);
    EXPECT_EQ(expectedRotation, resutObject.rotation);
}

TEST_F(GameObjectFactoryTests, create_ThreeObjects_ReturnCreateGameObjectsWithDifferentId)
{
    GameObjectFactoryTestable factory;

    auto resutObject1 { factory.create(GoType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resutObject2 { factory.create(GoType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resutObject3 { factory.create(GoType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resutObject1.id);
    EXPECT_EQ(1, resutObject2.id);
    EXPECT_EQ(2, resutObject3.id);
}

TEST_F(GameObjectFactoryTests, create_TwoFactoriesCreateOneObject_ReturnTwoObjectWithDifferentId)
{
    GameObjectFactory factory1;
    GameObjectFactory factory2;

    auto resutObject1 { factory1.create(GoType::PLAYER, { 0.0, 0.0 }, 0.0) };
    auto resutObject2 { factory2.create(GoType::PLAYER, { 0.0, 0.0 }, 0.0) };

    EXPECT_EQ(0, resutObject1.id);
    EXPECT_EQ(1, resutObject2.id);
}
