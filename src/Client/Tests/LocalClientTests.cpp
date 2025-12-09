#include <Client.hpp>
#include <LocalClient.hpp>
#include <MockInput.hpp>
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
    auto scene { std::make_unique<MockScene>() };
    auto input { std::make_unique<MockInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*input, start());
    EXPECT_CALL(*scene, show());
    LocalClient client { std::move(scene), std::move(input) };

    client.start();
}

TEST_F(LocalClientTests, stop_SinglePlayerGame_ShouldStopInputReading)
{
    auto scene { std::make_unique<MockScene>() };
    auto input { std::make_unique<MockInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*input, stop());
    EXPECT_CALL(*scene, hide());
    LocalClient client { std::move(scene), std::move(input) };

    client.stop();
}

TEST_F(LocalClientTests, receive_KeyboardY_ShouldDoNothing)
{
    auto scene { std::make_unique<MockScene>() };
    auto input { std::make_unique<MockInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*input, stop()).Times(0);
    GameCommand resultCommand { GameCommand::NoCommand };
    const GameConnection connection = [&resultCommand](const GameCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { std::move(scene), std::move(input) };
    client.connect(connection);

    client.receive("Keyboard: Y");

    EXPECT_EQ(GameCommand::NoCommand, resultCommand);
}

TEST_F(LocalClientTests, receive_KeyboardESC_ShouldStopAndSendGameCommand)
{
    auto scene { std::make_unique<MockScene>() };
    auto input { std::make_unique<MockInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*input, stop());
    EXPECT_CALL(*scene, hide());
    GameCommand resultCommand { GameCommand::NoCommand };
    const GameConnection connection = [&resultCommand](const GameCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { std::move(scene), std::move(input) };
    client.connect(connection);

    client.receive("Keyboard: ESC");

    EXPECT_EQ(GameCommand::Pause, resultCommand);
}
