#include <InputDispatcher.hpp>
#include <MockInputHandler.hpp>
#include <MockInputSource.hpp>
#include <gtest/gtest.h>

using namespace testing;

class InputDispatcherTestable : public InputDispatcher
{
public:
    using InputDispatcher::InputDispatcher;

    [[nodiscard]] const InputHandlers& getInputHandlers() const
    {
        return handlers;
    }
};

class InputDispatcherTests : public Test
{
public:
    static InputEvent getInputEvent(const InputEventType& type)
    {
        InputEvent event;
        event.type = type;
        return event;
    }
};

TEST_F(InputDispatcherTests, addHandler_OneHandler_InputHandlersContainsOneElement)
{
    auto handler { std::make_shared<MockInputHandler>() };
    InputDispatcherTestable dispatcher { nullptr };

    dispatcher.addHandler(handler);

    const auto& resultHandlers { dispatcher.getInputHandlers() };
    EXPECT_EQ(1, resultHandlers.size());
}

TEST_F(InputDispatcherTests, addHandler_ThreeHandlers_InputHandlersContainsThreeElements)
{
    auto handler1 { std::make_shared<MockInputHandler>() };
    auto handler2 { std::make_shared<MockInputHandler>() };
    auto handler3 { std::make_shared<MockInputHandler>() };
    InputDispatcherTestable dispatcher { nullptr };

    dispatcher.addHandler(handler1);
    dispatcher.addHandler(handler2);
    dispatcher.addHandler(handler3);

    const auto& resultHandlers { dispatcher.getInputHandlers() };
    EXPECT_EQ(3, resultHandlers.size());
}

TEST_F(InputDispatcherTests, dispatch_NoEventsAndNoHandlers_DoNothing)
{
    const std::vector<InputEvent> events {};
    auto source { std::make_shared<MockInputSource>() };
    EXPECT_CALL(*source, pollEvents()).WillOnce(Return(events));
    InputDispatcherTestable dispatcher { source };

    dispatcher.dispatch();
}

TEST_F(InputDispatcherTests, dispatch_OneQuitEventAndNoHandlers_DoNothing)
{
    InputEvent event;
    event.type = InputEventType::Quit;
    std::vector<InputEvent> events {};
    events.push_back(event);
    auto source { std::make_shared<MockInputSource>() };
    EXPECT_CALL(*source, pollEvents()).WillOnce(Return(events));
    InputDispatcherTestable dispatcher { source };

    dispatcher.dispatch();
}

TEST_F(InputDispatcherTests, dispatch_OneQuitEventAndOneHandlerButNotHandlingIt_DoNothing)
{
    std::vector<InputEvent> events {};
    events.push_back(getInputEvent(InputEventType::Quit));
    auto source { std::make_shared<MockInputSource>() };
    EXPECT_CALL(*source, pollEvents()).WillOnce(Return(events));
    auto handler { std::make_shared<MockInputHandler>() };
    EXPECT_CALL(*handler, handle(_)).WillOnce(Return(false));
    InputDispatcherTestable dispatcher { source };
    dispatcher.addHandler(handler);

    dispatcher.dispatch();
}

TEST_F(InputDispatcherTests, dispatch_OneQuitEventOneHandlerAndHandlingIt_HandlerHandleEvent)
{
    std::vector<InputEvent> events {};
    events.push_back(getInputEvent(InputEventType::Quit));
    auto source { std::make_shared<MockInputSource>() };
    EXPECT_CALL(*source, pollEvents()).WillOnce(Return(events));
    auto handler { std::make_shared<MockInputHandler>() };
    EXPECT_CALL(*handler, handle(_)).WillOnce(Return(true));
    InputDispatcherTestable dispatcher { source };
    dispatcher.addHandler(handler);

    dispatcher.dispatch();
}

TEST_F(InputDispatcherTests, dispatch_OneQuitEventTwoHandlersAndFirstHandlingIt_FirstHandlerHandleEventButSecondNot)
{
    std::vector<InputEvent> events {};
    events.push_back(getInputEvent(InputEventType::Quit));
    auto source { std::make_shared<MockInputSource>() };
    EXPECT_CALL(*source, pollEvents()).WillOnce(Return(events));
    auto handler1 { std::make_shared<MockInputHandler>() };
    EXPECT_CALL(*handler1, handle(_)).WillOnce(Return(true));
    auto handler2 { std::make_shared<MockInputHandler>() };
    EXPECT_CALL(*handler2, handle(_)).Times(0);
    InputDispatcherTestable dispatcher { source };
    dispatcher.addHandler(handler1);
    dispatcher.addHandler(handler2);

    dispatcher.dispatch();
}

TEST_F(InputDispatcherTests, dispatch_ThreeDifferentEventOneHandlerAndHandlingSecondEvent_HandlerHandleOnlyOneEvent)
{
    std::vector<InputEvent> events {};
    events.push_back(getInputEvent(InputEventType::Quit));
    events.push_back(getInputEvent(InputEventType::MouseMove));
    events.push_back(getInputEvent(InputEventType::KeyPressed));
    auto source { std::make_shared<MockInputSource>() };
    EXPECT_CALL(*source, pollEvents()).WillOnce(Return(events));
    auto handler { std::make_shared<MockInputHandler>() };
    EXPECT_CALL(*handler, handle(_)).WillOnce(Return(false)).WillOnce(Return(true)).WillOnce(Return(false));
    InputDispatcherTestable dispatcher { source };
    dispatcher.addHandler(handler);

    dispatcher.dispatch();
}
