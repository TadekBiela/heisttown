#include <ButtonWidget.hpp>
#include <InputEvent.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <WidgetControl.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <variant>

using namespace testing;

class ButtonWidgetTestable : public ButtonWidget
{
public:
    using ButtonWidget::ButtonWidget;

    ControlConnection getControlConnection() const
    {
        return controlConnection;
    }
};

class ButtonWidgetTests : public Test
{
public:
    sf::RenderWindow& getWindow()
    {
        return window;
    }

private:
    sf::RenderWindow window;
};

TEST_F(ButtonWidgetTests, getType_DefaultBehavior_ReturnButtonType)
{
    const ButtonWidgetTestable button {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };

    const auto resultType { button.getType() };

    EXPECT_EQ(WidgetType::BUTTON, resultType);
}

TEST_F(ButtonWidgetTests, connect_EmptyFunction_AsignEmptyFunctionAsConnection)
{
    auto connection = [](const WidgetCommand&) {};
    ButtonWidgetTestable button {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };

    button.connect(connection);

    EXPECT_TRUE(button.getControlConnection() != nullptr);
}

TEST_F(ButtonWidgetTests, handle_NotHandledEvent_ReturnFalse)
{
    InputEvent event {};
    event.type = InputEventType::KeyPressed;
    ButtonWidgetTestable button {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };
    button.show();

    const bool result = button.handle(event);

    EXPECT_FALSE(result);
}

TEST_F(ButtonWidgetTests, handle_LeftMouseButtonPressedEventInsideButtonShapeButButtonNotVisible_ReturnFalse)
{
    WidgetCommand resultCommand;
    auto connection = [&resultCommand](const WidgetCommand& command)
    {
        resultCommand = command;
    };
    InputEvent event {};
    event.type = InputEventType::MouseButtonPressed;
    event.data = MouseButtonData { MouseButton::Left, 50.0F, 25.0F };
    ButtonWidgetTestable button {
        WidgetGeometry { 0.0F, 0.0F, 100.0F, 50.0F },
        "TestButton",
        std::string {},
        getWindow()
    };
    button.connect(connection);

    const bool result = button.handle(event);

    EXPECT_TRUE(resultCommand.empty());
    EXPECT_FALSE(result);
}

TEST_F(ButtonWidgetTests, handle_RightMouseButtonPressedEventInsideButtonShapeAndButtonVisible_ReturnFalse)
{
    WidgetCommand resultCommand;
    auto connection = [&resultCommand](const WidgetCommand& command)
    {
        resultCommand = command;
    };
    InputEvent event {};
    event.type = InputEventType::MouseButtonPressed;
    event.data = MouseButtonData { MouseButton::Right, 50.0F, 25.0F };
    ButtonWidgetTestable button {
        WidgetGeometry { 0.0F, 0.0F, 100.0F, 50.0F },
        "TestButton",
        std::string {},
        getWindow()
    };
    button.connect(connection);
    button.show();

    const bool result = button.handle(event);

    EXPECT_TRUE(resultCommand.empty());
    EXPECT_FALSE(result);
}

TEST_F(ButtonWidgetTests, handle_LeftMouseButtonPressedEventOutsideButtonShapeAndButtonVisible_ReturnFalse)
{
    WidgetCommand resultCommand;
    auto connection = [&resultCommand](const WidgetCommand& command)
    {
        resultCommand = command;
    };
    InputEvent event {};
    event.type = InputEventType::MouseButtonPressed;
    event.data = MouseButtonData { MouseButton::Left, 150.0F, 25.0F };
    ButtonWidgetTestable button {
        WidgetGeometry { 0.0F, 0.0F, 100.0F, 50.0F },
        "TestButton",
        std::string {},
        getWindow()
    };
    button.connect(connection);
    button.show();

    const bool result = button.handle(event);

    EXPECT_TRUE(resultCommand.empty());
    EXPECT_FALSE(result);
}

TEST_F(ButtonWidgetTests, handle_LeftMouseButtonPressedEventInsideButtonShapeAndButtonVisible_ExecuteConnectionWithButtonTextAndReturnTrue)
{
    const WidgetText expectedWidgetText { "TestButton" };
    WidgetCommand resultCommand;
    auto connection = [&resultCommand](const WidgetCommand& command)
    {
        resultCommand = command;
    };
    InputEvent event {};
    event.type = InputEventType::MouseButtonPressed;
    event.data = MouseButtonData { MouseButton::Left, 50.0F, 25.0F };
    ButtonWidgetTestable button {
        WidgetGeometry { 0.0F, 0.0F, 100.0F, 50.0F },
        expectedWidgetText,
        std::string {},
        getWindow()
    };
    button.connect(connection);
    button.show();

    const bool result = button.handle(event);

    EXPECT_EQ(expectedWidgetText, resultCommand);
    EXPECT_TRUE(result);
}
