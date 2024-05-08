#include <LocalClient.hpp>
#include <MockGameDisplay.hpp>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class LocalClientTests : public Test
{
};

TEST_F(LocalClientTests, run_SinglePlayerGame_ShouldShowGameDisplay)
{
    auto display { std::make_unique<MockGameDisplay>() };
    EXPECT_CALL(*display, show());
    LocalClient client { std::move(display) };

    client.startSinglePlayerGame();
}
