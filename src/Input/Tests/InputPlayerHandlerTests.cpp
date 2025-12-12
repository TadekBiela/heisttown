#include "InputPlayerHandler.hpp"
#include <gtest/gtest.h>

using namespace testing;

class InputPlayerHandlerTests : public Test
{
};

TEST_F(InputPlayerHandlerTests, handle_NotSupportedEvent_ReturnFalse)
{
    InputEvent event;
    event.type = InputEventType::NotSupported;
    InputPlayerHandler handler;

    auto result = handler.handle(event);

    EXPECT_FALSE(result);
    EXPECT_EQ(PlayerStatus{}, handler.getPlayerStatus());
}

TEST_F(InputPlayerHandlerTests, handle_QuitEvent_ReturnFalse)
{
    InputEvent event;
    event.type = InputEventType::Quit;
    InputPlayerHandler handler;

    auto result = handler.handle(event);

    EXPECT_FALSE(result);
    EXPECT_EQ(PlayerStatus{}, handler.getPlayerStatus());
}

struct HandleParams
{
    std::vector<InputEvent> inputEvents;
    Direction expectedMoveDirection ;
    Velocity expectedMoveVelocity;
};

class InputPlayerHandlerTestsWithKeyEvents : public TestWithParam<HandleParams>
{
};

const std::vector<HandleParams> handleParams {
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::None } }
        },
        Direction::FRONT,
        Velocity { 0.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Up } }
        },
        Direction::FRONT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Right } }
        },
        Direction::RIGHT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Down } }
        },
        Direction::BACK,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } }
        },
        Direction::LEFT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Up } },
            InputEvent{ InputEventType::KeyReleased, KeyData { Key::Up } }
        },
        Direction::FRONT,
        Velocity { 0.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Up } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Right } }
        },
        Direction::FRONT_RIGHT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Up } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } }
        },
        Direction::FRONT_LEFT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Right } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Up } }
        },
        Direction::FRONT_RIGHT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Up } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } }
        },
        Direction::FRONT_LEFT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Down } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } }
        },
        Direction::BACK_LEFT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Down } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Right } }
        },
        Direction::BACK_RIGHT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Down } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } },
            InputEvent{ InputEventType::KeyReleased, KeyData { Key::Down } }
        },
        Direction::LEFT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Right } }
        },
        Direction::RIGHT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Right } },
            InputEvent{ InputEventType::KeyReleased, KeyData { Key::Right } }
        },
        Direction::LEFT,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } },
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Down } },
            InputEvent{ InputEventType::KeyReleased, KeyData { Key::Left } }
        },
        Direction::BACK,
        Velocity { 1.0F }
    },
    {
        {
            InputEvent{ InputEventType::KeyPressed, KeyData { Key::Left } },
            InputEvent{ InputEventType::KeyReleased, KeyData { Key::None } }
        },
        Direction::LEFT,
        Velocity { 1.0F }
    }
};

TEST_P(InputPlayerHandlerTestsWithKeyEvents, handle_KeyPressedAndOrReleasedEvents_SetDirectionAndVelocity)
{
    const auto& params = GetParam();
    PlayerStatus expectedPlayerStatus;
    expectedPlayerStatus.moveDirection = params.expectedMoveDirection;
    expectedPlayerStatus.moveVelocity = params.expectedMoveVelocity;
    InputPlayerHandler handler;

    for(const auto& event : params.inputEvents)
    {
        handler.handle(event);
    }

    EXPECT_EQ(expectedPlayerStatus, handler.getPlayerStatus());
}

INSTANTIATE_TEST_CASE_P(KeyEvents, InputPlayerHandlerTestsWithKeyEvents, ValuesIn(handleParams));
