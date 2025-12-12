#include <Client.hpp>
#include <LocalClient.hpp>
#include <MockInputDispatcher.hpp>
#include <MockScene.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class LocalClientTests : public Test
{
};

TEST_F(LocalClientTests, start_SinglePlayerGame_ShouldStartInputReading)
{
    auto scene { std::make_shared<MockScene>() };
    auto dispatcher { std::make_shared<MockInputDispatcher>() };
    EXPECT_CALL(*dispatcher, addHandler(_));
    EXPECT_CALL(*scene, show());
    LocalClient client { scene, dispatcher };

    client.start();
}

TEST_F(LocalClientTests, stop_SinglePlayerGame_ShouldStopInputReading)
{
    auto scene { std::make_shared<MockScene>() };
    auto dispatcher { std::make_shared<MockInputDispatcher>() };
    EXPECT_CALL(*dispatcher, addHandler(_));
    EXPECT_CALL(*scene, hide());
    LocalClient client { scene, dispatcher };

    client.stop();
}

TEST_F(LocalClientTests, receive_KeyboardY_ShouldDoNothing)
{
    auto scene { std::make_shared<MockScene>() };
    auto dispatcher { std::make_shared<MockInputDispatcher>() };
    EXPECT_CALL(*dispatcher, addHandler(_));
    GameCommand resultCommand { GameCommand::NoCommand };
    const GameConnection connection = [&resultCommand](const GameCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { scene, dispatcher };
    client.connect(connection);

    client.receive("Keyboard: Y");

    EXPECT_EQ(GameCommand::NoCommand, resultCommand);
}

TEST_F(LocalClientTests, receive_KeyboardESC_ShouldStopAndSendGameCommand)
{
    auto scene { std::make_shared<MockScene>() };
    auto dispatcher { std::make_shared<MockInputDispatcher>() };
    EXPECT_CALL(*dispatcher, addHandler(_));
    EXPECT_CALL(*scene, hide());
    GameCommand resultCommand { GameCommand::NoCommand };
    const GameConnection connection = [&resultCommand](const GameCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { scene, dispatcher };
    client.connect(connection);

    client.receive("Keyboard: ESC");

    EXPECT_EQ(GameCommand::Pause, resultCommand);
}
