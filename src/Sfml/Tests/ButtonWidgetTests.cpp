#include <ButtonWidget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <WidgetControl.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>

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
    void SetUp() override
    {
        font = std::make_shared<sf::Font>();
        auto currentPath { std::filesystem::current_path() };
        currentPath = currentPath.parent_path();
        const auto fontPath { currentPath.string() + "/Font/PixelCode.ttf" };
        font->loadFromFile(fontPath);
    }

    std::shared_ptr<sf::Font> getFont()
    {
        return font;
    }

private:
    std::shared_ptr<sf::Font> font;
};

TEST_F(ButtonWidgetTests, getType_DefaultBehavior_ReturnButtonType)
{
    const ButtonWidgetTestable button { WidgetGeometry {}, std::string {}, std::string {}, getFont() };

    const auto resultType { button.getType() };

    EXPECT_EQ(WidgetType::BUTTON, resultType);
}

TEST_F(ButtonWidgetTests, connect_EmptyFunction_AsignEmptyFunctionAsConnection)
{
    auto connection = [](const WidgetCommand&) {};
    ButtonWidgetTestable button { WidgetGeometry {}, std::string {}, std::string {}, getFont() };

    button.connect(connection);

    EXPECT_TRUE(button.getControlConnection() != nullptr);
}

TEST_F(ButtonWidgetTests, handle_NotHandledEvent_ReturnFalse)
{
    sf::Event event {};
    event.type = sf::Event::EventType::Resized;
    ButtonWidgetTestable button { WidgetGeometry {}, std::string {}, std::string {}, getFont() };
    button.show();

    const bool result = button.handle(event);

    EXPECT_FALSE(result);
}

// NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
TEST_F(ButtonWidgetTests, handle_LeftMouseButtonPressedEventInsideButtonShapeButButtonNotVisible_ReturnFalse)
{
    WidgetCommand resultCommand;
    auto connection = [&resultCommand](const WidgetCommand& command)
    {
        resultCommand = command;
    };
    sf::Event event {};
    event.type = sf::Event::EventType::MouseButtonPressed;
    auto& mouseButton { event.mouseButton };
    mouseButton.button = sf::Mouse::Button::Left;
    mouseButton.x = 50.0;
    mouseButton.y = 25.0;
    ButtonWidgetTestable button { WidgetGeometry { 0.0, 0.0, 100.0, 50.0 }, "TestButton", std::string {}, getFont() };
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
    sf::Event event {};
    event.type = sf::Event::EventType::MouseButtonPressed;
    auto& mouseButton { event.mouseButton };
    mouseButton.button = sf::Mouse::Button::Right;
    mouseButton.x = 50.0;
    mouseButton.y = 25.0;
    ButtonWidgetTestable button { WidgetGeometry { 0.0, 0.0, 100.0, 50.0 }, "TestButton", std::string {}, getFont() };
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
    sf::Event event {};
    event.type = sf::Event::EventType::MouseButtonPressed;
    auto& mouseButton { event.mouseButton };
    mouseButton.button = sf::Mouse::Button::Left;
    mouseButton.x = 150.0;
    mouseButton.y = 25.0;
    ButtonWidgetTestable button { WidgetGeometry { 0.0, 0.0, 100.0, 50.0 }, "TestButton", std::string {}, getFont() };
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
    sf::Event event {};
    event.type = sf::Event::EventType::MouseButtonPressed;
    auto& mouseButton { event.mouseButton };
    mouseButton.button = sf::Mouse::Button::Left;
    mouseButton.x = 50.0;
    mouseButton.y = 25.0;
    ButtonWidgetTestable button { WidgetGeometry { 0.0, 0.0, 100.0, 50.0 }, expectedWidgetText, std::string {}, getFont() };
    button.connect(connection);
    button.show();

    const bool result = button.handle(event);

    EXPECT_EQ(expectedWidgetText, resultCommand);
    EXPECT_TRUE(result);
}
// NOLINTEND(cppcoreguidelines-pro-type-union-access)
