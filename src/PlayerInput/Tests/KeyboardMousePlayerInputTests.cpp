#include <KeyboardMousePlayerInput.hpp>
#include <MockKeyboard.hpp>
#include <gtest/gtest.h>

using namespace testing;

class KeyboardMousePlayerInputTests : public Test
{
};

TEST_F(KeyboardMousePlayerInputTests, start_SingleDefaultExecution_ShouldRunNewThreadWithKeyboardReading)
{
    auto keyboard { std::make_unique<MockKeyboard>() };
    Sequence seq;
    EXPECT_CALL(*keyboard, enable());
    EXPECT_CALL(*keyboard, isEnabled()).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(*keyboard, getPressedKey()).WillOnce(Return(27));
    EXPECT_CALL(*keyboard, disable()).Times(2);
    PlayerInputReceiver receiver { [](const PlayerInputCommand&) {} };
    KeyboardMousePlayerInput input { std::move(keyboard) };
    input.setInputReceiver(receiver);

    input.start();
}

TEST_F(KeyboardMousePlayerInputTests, start_FirstPressedQNextEsc_ShouldIgnoreFirstOneAndReactToEsc)
{
    auto keyboard { std::make_unique<MockKeyboard>() };
    Sequence seq;
    EXPECT_CALL(*keyboard, enable());
    EXPECT_CALL(*keyboard, isEnabled()).WillOnce(Return(true)).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(*keyboard, getPressedKey()).WillOnce(Return('q')).WillOnce(Return(27));
    EXPECT_CALL(*keyboard, disable()).Times(2);
    PlayerInputReceiver receiver { [](const PlayerInputCommand&) {} };
    KeyboardMousePlayerInput input { std::move(keyboard) };
    input.setInputReceiver(receiver);

    input.start();
}

TEST_F(KeyboardMousePlayerInputTests, start_DoubleStart_ShouldRunNewThreadOnlyOnce)
{
    auto keyboard { std::make_unique<MockKeyboard>() };
    Sequence seq;
    EXPECT_CALL(*keyboard, enable());
    EXPECT_CALL(*keyboard, isEnabled()).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(*keyboard, getPressedKey()).WillRepeatedly(Return('q'));
    EXPECT_CALL(*keyboard, disable());
    PlayerInputReceiver receiver { [](const PlayerInputCommand&) {} };
    KeyboardMousePlayerInput input { std::move(keyboard) };
    input.setInputReceiver(receiver);

    input.start();
    input.start();
}

TEST_F(KeyboardMousePlayerInputTests, stop_SingleDefaultExecution_ShouldRunNewThreadWithKeyboardReadingAndDisableKeyboard)
{
    auto keyboard { std::make_unique<MockKeyboard>() };
    Sequence seq;
    EXPECT_CALL(*keyboard, enable());
    EXPECT_CALL(*keyboard, isEnabled()).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(*keyboard, getPressedKey()).WillOnce(Return(27));
    EXPECT_CALL(*keyboard, disable()).Times(3);
    PlayerInputReceiver receiver { [](const PlayerInputCommand&) {} };
    KeyboardMousePlayerInput input { std::move(keyboard) };
    input.setInputReceiver(receiver);
    input.start();

    input.stop();
}
