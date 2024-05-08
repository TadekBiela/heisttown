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
