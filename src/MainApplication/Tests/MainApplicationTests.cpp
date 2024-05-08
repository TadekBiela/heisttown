#include <MainApplication.hpp>
#include <MockClient.hpp>
#include <MockMenuController.hpp>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class MainApplicationTests : public Test
{
};

TEST_F(MainApplicationTests, constructor_DefaultBehavior_ShouldConnectController)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));

    MainApplication application { std::move(menuController), std::move(client) };
}

TEST_F(MainApplicationTests, control_SinglePlayerPlay_ShouldRunClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*client, run());
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("SinglePlayer->Play");
}

TEST_F(MainApplicationTests, control_DummyCommand_ShouldDoNothing)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*client, run()).Times(0);
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("Dummy->Command");
}

TEST_F(MainApplicationTests, control_SinglePlayerBack_ShouldDoNothing)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*client, run()).Times(0);
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("SinglePlayer->Back");
}
