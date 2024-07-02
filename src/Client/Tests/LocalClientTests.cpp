#include <LocalClient.hpp>
#include <MockGameDisplay.hpp>
#include <MockPlayerInput.hpp>
#include <PlayerInput.hpp>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class LocalClientTests : public Test
{
};

TEST_F(LocalClientTests, start_SinglePlayerGame_ShouldShowGameDisplayAndStartInputReading)
{
    auto display { std::make_unique<MockGameDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, show());
    EXPECT_CALL(*input, start());
    LocalClient client { std::move(display), std::move(input) };

    client.start();
}

TEST_F(LocalClientTests, stop_SinglePlayerGame_ShouldHideGameDisplayAndStopInputReading)
{
    auto display { std::make_unique<MockGameDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, hide());
    EXPECT_CALL(*input, stop());
    LocalClient client { std::move(display), std::move(input) };

    client.stop();
}

TEST_F(LocalClientTests, receive_KeyboardY_ShouldDoNothing)
{
    auto display { std::make_unique<MockGameDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, hide()).Times(0);
    EXPECT_CALL(*input, stop()).Times(0);
    MainCommand resultCommand;
    MainControlConnection mainConnection = [&resultCommand](const MainCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { std::move(display), std::move(input) };
    client.setMainControl(mainConnection);

    client.receive("Keyboard: Y");

    EXPECT_TRUE(resultCommand.empty());
}

TEST_F(LocalClientTests, receive_KeyboardESC_ShouldStopAndSendMainCommand)
{
    auto display { std::make_unique<MockGameDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, hide());
    EXPECT_CALL(*input, stop());
    MainCommand resultCommand;
    MainControlConnection mainConnection = [&resultCommand](const MainCommand& command)
    {
        resultCommand = command;
    };
    LocalClient client { std::move(display), std::move(input) };
    client.setMainControl(mainConnection);

    client.receive("Keyboard: ESC");

    EXPECT_STREQ("SinglePlayer->Pause", resultCommand.c_str());
}
