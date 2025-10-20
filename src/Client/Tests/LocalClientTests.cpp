#include <Client.hpp>
#include <LocalClient.hpp>
#include <MockDisplay.hpp>
#include <MockPlayerInput.hpp>
#include <PlayerInput.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <utility>

using namespace testing;

class LocalClientTests : public Test
{
};

TEST_F(LocalClientTests, start_SinglePlayerGame_ShouldShowDisplayAndStartInputReading)
{
    auto display { std::make_unique<MockDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, show());
    EXPECT_CALL(*input, start());
    LocalClient client { std::move(display), std::move(input) };

    client.start();
}

TEST_F(LocalClientTests, stop_SinglePlayerGame_ShouldHideDisplayAndStopInputReading)
{
    auto display { std::make_unique<MockDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, hide());
    EXPECT_CALL(*input, stop());
    LocalClient client { std::move(display), std::move(input) };

    client.stop();
}

TEST_F(LocalClientTests, receive_KeyboardY_ShouldDoNothing)
{
    auto display { std::make_unique<MockDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, hide()).Times(0);
    EXPECT_CALL(*input, stop()).Times(0);
    GameCommand resultCommand { GameCommand::NoCommand };
    const GameConnection connection = [&resultCommand](const GameCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { std::move(display), std::move(input) };
    client.connect(connection);

    client.receive("Keyboard: Y");

    EXPECT_EQ(GameCommand::NoCommand, resultCommand);
}

TEST_F(LocalClientTests, receive_KeyboardESC_ShouldStopAndSendGameCommand)
{
    auto display { std::make_unique<MockDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, hide());
    EXPECT_CALL(*input, stop());
    GameCommand resultCommand { GameCommand::NoCommand };
    const GameConnection connection = [&resultCommand](const GameCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { std::move(display), std::move(input) };
    client.connect(connection);

    client.receive("Keyboard: ESC");

    EXPECT_EQ(GameCommand::Pause, resultCommand);
}
