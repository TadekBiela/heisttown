#include <Button.h>
#include <MockWidget.h>
#include <Widget.h>
#include <functional>
#include <gtest/gtest.h>

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
    ) : Button(
            display,
            geometry,
            text,
            style
        )
    {}

    QPushButton* getImplementation()
    {
        return buttonImpl.get();
    }
};

TEST_F(ButtonTests, connect_MockedConnectedOutput_ShouldExecuteOutputFunctionWithButtonText)
{
    const WidgetText expectedText { "ButtonTestText" };
    MockWidget outputWidget;
    EXPECT_CALL(outputWidget, setText(expectedText));
    ConnectionOutput outputFunction = std::bind(&MockWidget::setText, &outputWidget, std::placeholders::_1);
    ButtonTestable button(
        nullptr,
        { 100, 50, 30, 20 },
        expectedText,
        ""
    );

    button.connect(outputFunction);
    button.getImplementation()->click();
}
