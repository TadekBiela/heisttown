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
    EXPECT_CALL(*client, start());
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("SinglePlayer->Play");
}

TEST_F(MainApplicationTests, control_DummyCommand_ShouldDoNothing)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*client, start()).Times(0);
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("Dummy->Command");
}

TEST_F(MainApplicationTests, control_SinglePlayerBack_ShouldDoNothing)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*client, start()).Times(0);
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("SinglePlayer->Back");
}

TEST_F(MainApplicationTests, control_SinglePlayerPause_ShouldSetPauseMenuOnMenuController)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*menuController, control("Pause"));
    EXPECT_CALL(*client, start()).Times(0);
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("SinglePlayer->Pause");
}

TEST_F(MainApplicationTests, control_PauseAbort_ShouldAbortCurrentGameSessionOnClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*menuController, showMenu());
    EXPECT_CALL(*client, stop());
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("Pause->Abort");
}

TEST_F(MainApplicationTests, control_PauseContinue_ShouldBackToCurrentGameSessionOnClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, setMainControl(_));
    EXPECT_CALL(*menuController, showMenu()).Times(0);
    EXPECT_CALL(*client, start());
    MainApplication application { std::move(menuController), std::move(client) };

    application.control("Pause->Continue");
}
