#include <Client.hpp>
#include <IMenuController.hpp>
#include <MainApplication.hpp>
#include <MockClient.hpp>
#include <MockMenuController.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <utility>

using namespace testing;

class MainApplicationTests : public Test
{
};

TEST_F(MainApplicationTests, constructor_DefaultBehavior_ShouldConnectController)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));

    MainApplication { std::move(menuController), std::move(client), []() {} };
}

TEST_F(MainApplicationTests, handle_MenuCommandSinglePlayerPlay_ShouldRunClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start());
    MainApplication application { std::move(menuController), std::move(client), []() {} };

    application.handle(MenuCommand::StartSinglePlayer);
}

TEST_F(MainApplicationTests, handle_MenuCommandNoCommand_ShouldDoNothing)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start()).Times(0);
    MainApplication application { std::move(menuController), std::move(client), []() {} };

    application.handle(MenuCommand::NoCommand);
}

TEST_F(MainApplicationTests, handle_MenuCommandAbort_ShouldAbortCurrentGameSessionOnClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, showMenu());
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, stop());
    MainApplication application { std::move(menuController), std::move(client), []() {} };

    application.handle(MenuCommand::Abort);
}

TEST_F(MainApplicationTests, handle_MenuCommandContinue_ShouldBackToCurrentGameSessionOnClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, showMenu()).Times(0);
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start());
    MainApplication application { std::move(menuController), std::move(client), []() {} };

    application.handle(MenuCommand::Continue);
}

TEST_F(MainApplicationTests, handle_GameCommandSinglePlayerPause_ShouldSetPauseSinglePlayerOnMenuController)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, handle("Pause"));
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start()).Times(0);
    MainApplication application { std::move(menuController), std::move(client), []() {} };

    application.handle(GameCommand::Pause);
}

TEST_F(MainApplicationTests, handle_MainMenuExit_ShouldDestroyApplication)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    int callCounter { 0 };
    auto guiExitCallback = [&callCounter]()
    {
        callCounter++;
    };
    MainApplication application { std::move(menuController), std::move(client), guiExitCallback };

    application.handle(MenuCommand::Exit);

    EXPECT_EQ(1, callCounter);
}

TEST_F(MainApplicationTests, setGuiExitCallback_DefaultBehavior_ShouldSetGuiExitCallback)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto client { std::make_unique<MockClient>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    int expectedCallCounter { 0 };
    auto guiExitCallback = [&expectedCallCounter]()
    {
        expectedCallCounter++;
    };
    MainApplication { std::move(menuController), std::move(client), guiExitCallback };

    EXPECT_EQ(0, expectedCallCounter);
}
