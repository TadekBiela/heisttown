#include <Client.hpp>
#include <IMenuController.hpp>
#include <MainApplication.hpp>
#include <MockClient.hpp>
#include <MockMenuController.hpp>
#include <MockPlayerInput.hpp>
#include <MockScene.hpp>
#include <MockServer.hpp>
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
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));

    MainApplication {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };
}

TEST_F(MainApplicationTests, handle_MenuCommandSinglePlayerPlay_ShouldRunClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start());
    EXPECT_CALL(*server, start());
    EXPECT_CALL(*server, connect(_));
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };

    application.handle(MenuCommand::StartSinglePlayer);
}

TEST_F(MainApplicationTests, handle_MenuCommandNoCommand_ShouldDoNothing)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start()).Times(0);
    EXPECT_CALL(*server, start()).Times(0);
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };

    application.handle(MenuCommand::NoCommand);
}

TEST_F(MainApplicationTests, handle_MenuCommandAbort_ShouldAbortCurrentGameSessionOnClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, showMenu());
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, stop());
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };

    application.handle(MenuCommand::Abort);
}

TEST_F(MainApplicationTests, handle_MenuCommandContinue_ShouldBackToCurrentGameSessionOnClient)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, showMenu()).Times(0);
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start());
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };

    application.handle(MenuCommand::Continue);
}

TEST_F(MainApplicationTests, handle_GameCommandSinglePlayerPause_ShouldSetPauseSinglePlayerOnMenuController)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, handle("Pause"));
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, stop());
    EXPECT_CALL(*client, start()).Times(0);
    EXPECT_CALL(*server, start()).Times(0);
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };

    application.handle(GameCommand::Pause);
}

TEST_F(MainApplicationTests, handle_GameCommandNoCommand_ShouldDoNothing)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, handle(_)).Times(0);
    EXPECT_CALL(*client, connect(_));
    EXPECT_CALL(*client, start()).Times(0);
    EXPECT_CALL(*server, start()).Times(0);
    EXPECT_CALL(*client, stop()).Times(0);
    EXPECT_CALL(*server, stop()).Times(0);
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };

    application.handle(GameCommand::NoCommand);
}

TEST_F(MainApplicationTests, handle_MainMenuExit_ShouldDestroyApplication)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    int callCounter { 0 };
    auto guiExitCallback = [&callCounter]()
    {
        callCounter++;
    };
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        guiExitCallback,
        client,
        std::move(server)
    };

    application.handle(MenuCommand::Exit);

    EXPECT_EQ(1, callCounter);
}

TEST_F(MainApplicationTests, setGuiExitCallback_DefaultBehavior_ShouldSetGuiExitCallback)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*client, connect(_));
    int expectedCallCounter { 0 };
    auto guiExitCallback = [&expectedCallCounter]()
    {
        expectedCallCounter++;
    };
    MainApplication {
        std::move(menuController),
        scene,
        std::move(input),
        guiExitCallback,
        client,
        std::move(server)
    };

    EXPECT_EQ(0, expectedCallCounter);
}

TEST_F(MainApplicationTests, run_defaultBehavior_ShowMenu)
{
    auto menuController { std::make_unique<MockMenuController>() };
    auto scene { std::make_shared<MockScene>() };
    auto input { std::make_unique<MockPlayerInput>() };
    auto client { std::make_shared<MockClient>() };
    auto server { std::make_unique<MockServer>() };
    EXPECT_CALL(*menuController, connect(_));
    EXPECT_CALL(*menuController, showMenu());
    EXPECT_CALL(*client, connect(_));
    MainApplication application {
        std::move(menuController),
        scene,
        std::move(input),
        []() {},
        client,
        std::move(server)
    };

    application.run();
}
