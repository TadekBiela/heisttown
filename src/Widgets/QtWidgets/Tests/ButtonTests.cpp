#include <Button.h>
#include <MockWidget.h>
#include <Widget.h>
#include <functional>
#include <gtest/gtest.h>

using namespace testing;

class ButtonTests : public testing::Test
{
};

class ButtonTestable : public Button
{
public:
    ButtonTestable(
        const std::shared_ptr<QWidget>& display,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    )
        : Button(
              display,
              geometry,
              text,
              style
          )
    {
    }

    auto getImplementation() -> QPushButton*
    {
        return buttonImpl.get();
    }
};

TEST_F(ButtonTests, connect_MockedConnectedOutput_ShouldExecuteOutputFunctionWithButtonText)
{
    MockWidget outputWidget;
    EXPECT_CALL(outputWidget, setText(_));
    ControlConnection controlConnection = [&](const WidgetCommand& command)
    {
        outputWidget.setText(command);
    };
    ButtonTestable button(
        nullptr,
        { 100, 50, 30, 20 },
        "",
        ""
    );

    button.connect(controlConnection);
    button.getImplementation()->click();
}
