#include <LocalClient.hpp>
#include <MockGameDisplay.hpp>
#include <MockPlayerInput.hpp>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class LocalClientTests : public Test
{
};

TEST_F(LocalClientTests, startSinglePlayerGame_SinglePlayerGame_ShouldShowGameDisplayAndStartInputReading)
{
    auto display { std::make_unique<MockGameDisplay>() };
    auto input { std::make_unique<MockPlayerInput>() };
    EXPECT_CALL(*input, setInputReceiver(_));
    EXPECT_CALL(*display, show());
    EXPECT_CALL(*input, start());
    LocalClient client { std::move(display), std::move(input) };

    client.startSinglePlayerGame();
}
