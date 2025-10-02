#include <Menu.hpp>
#include <MockWidget.hpp>
#include <MockWidgetWithControl.hpp>
#include <Widget.hpp>
#include <WidgetControl.hpp>
#include <WidgetType.hpp>
#include <functional>
#include <gtest/gtest.h>
#include <initializer_list>
#include <memory>
#include <utility>

using namespace testing;

class MenuTestable : public Menu
{
public:
    [[nodiscard]] const ControlWidgets& getControlWidgets() const
    {
        return controlWidgets;
    }
    [[nodiscard]] const StaticWidgets& getStaticWidgets() const
    {
        return staticWidgets;
    }
};

using MenuInitList = std::initializer_list<std::pair<WidgetType, WidgetText>>;
using MockWidgetGetter = const std::function<std::unique_ptr<MockWidget>(const WidgetType&)>&;

class MenuTests : public Test
{
public:
    static std::unique_ptr<MockWidget> getMockWidgetWithExpectedShow(const WidgetType& type)
    {
        auto widget { getMockWidget(type) };
        EXPECT_CALL(*widget, show());
        return widget;
    }

    static std::unique_ptr<MockWidget> getMockWidgetWithExpectedHide(const WidgetType& type)
    {
        auto widget { getMockWidget(type) };
        EXPECT_CALL(*widget, hide());
        return widget;
    }

    static std::unique_ptr<MockWidget> getMockWidget(const WidgetType& type)
    {
        auto widget { std::make_unique<MockWidget>() };
        EXPECT_CALL(*widget, getType()).WillRepeatedly(Return(type));
        return widget;
    }

    static std::unique_ptr<MockWidgetWithControl> getMockWidgetWithControlWithExpectedShow(const WidgetType& type)
    {
        auto widget { getMockWidgetWithControl(type) };
        EXPECT_CALL(*widget, show());
        return widget;
    }

    static std::unique_ptr<MockWidgetWithControl> getMockWidgetWithControlWithExpectedHide(const WidgetType& type)
    {
        auto widget { getMockWidgetWithControl(type) };
        EXPECT_CALL(*widget, hide());
        return widget;
    }

    static std::unique_ptr<MockWidgetWithControl> getMockWidgetWithControlWithExpectedConnect(const WidgetType& type)
    {
        auto widget { getMockWidgetWithControl(type) };
        EXPECT_CALL(*widget, connect(_));
        return widget;
    }

    static std::unique_ptr<MockWidgetWithControl> getMockWidgetWithControl(const WidgetType& type)
    {
        auto widget { std::make_unique<MockWidgetWithControl>() };
        EXPECT_CALL(*widget, getType()).WillRepeatedly(Return(type));
        return widget;
    }
};

TEST_F(MenuTests, addWidget_ButtonWidget_ShouldAddButtonToControlWidgets)
{
    MenuTestable menu;

    menu.addWidget(getMockWidgetWithControl(WidgetType::BUTTON));

    ASSERT_EQ(1, menu.getControlWidgets().size());
    EXPECT_EQ(WidgetType::BUTTON, menu.getControlWidgets().at(0)->getType());
    EXPECT_EQ(0, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, addWidget_LabelWidget_ShouldAddLabeToStaticWidgets)
{
    MenuTestable menu;

    menu.addWidget(getMockWidget(WidgetType::LABEL));

    EXPECT_EQ(0, menu.getControlWidgets().size());
    ASSERT_EQ(1, menu.getStaticWidgets().size());
    EXPECT_EQ(WidgetType::LABEL, menu.getStaticWidgets().at(0)->getType());
}

TEST_F(MenuTests, addWidget_DifferentWidgets_ShouldAddWidgetsRegardingToType)
{
    MenuTestable menu;

    menu.addWidget(getMockWidget(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithControl(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControl(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControl(WidgetType::BUTTON));
    menu.addWidget(getMockWidget(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithControl(WidgetType::BUTTON));

    EXPECT_EQ(4, menu.getControlWidgets().size());
    EXPECT_EQ(2, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsOneStaticWidget_ShouldShowWidget)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));

    menu.show();

    EXPECT_EQ(1, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeStaticWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));

    menu.show();

    EXPECT_EQ(3, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsOneControlWidget_ShouldShowWidget)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithControlWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(1, menu.getControlWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeControlWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithControlWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(3, menu.getControlWidgets().size());
}

TEST_F(MenuTests, show_ContainsTwoStaticAndControlWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithControlWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(2, menu.getStaticWidgets().size());
    EXPECT_EQ(2, menu.getControlWidgets().size());
}

TEST_F(MenuTests, hide_ContainsOneStaticWidget_ShouldHideWidget)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));

    menu.hide();

    EXPECT_EQ(1, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, hide_ContainsThreeStaticWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));

    menu.hide();

    EXPECT_EQ(3, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, hide_ContainsOneControlWidget_ShouldHideWidget)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithControlWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(1, menu.getControlWidgets().size());
}

TEST_F(MenuTests, hide_ContainsThreeControlWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithControlWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(3, menu.getControlWidgets().size());
}

TEST_F(MenuTests, hide_ContainsTwoStaticAndControlWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithControlWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(2, menu.getStaticWidgets().size());
    EXPECT_EQ(2, menu.getControlWidgets().size());
}

TEST_F(MenuTests, connect_ContainsNoWidgets_ShouldDoNothing)
{
    MenuTestable menu {};
    ControlConnection controlConnection { [](const WidgetCommand&) {} };

    menu.connect(controlConnection);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(0, menu.getControlWidgets().size());
}

TEST_F(MenuTests, connect_ContainsOneStaticWidget_ShouldDoNothing)
{
    MenuTestable menu;
    menu.addWidget(getMockWidget(WidgetType::LABEL));
    ControlConnection controlConnection { [](const WidgetCommand&) {} };

    menu.connect(controlConnection);

    EXPECT_EQ(1, menu.getStaticWidgets().size());
    EXPECT_EQ(0, menu.getControlWidgets().size());
}

TEST_F(MenuTests, connect_ContainsOneControlWidget_ShouldConnectWidgetToOutput)
{
    ControlConnection controlConnection { [](const WidgetCommand&) {} };
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithControlWithExpectedConnect(WidgetType::BUTTON));

    menu.connect(controlConnection);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(1, menu.getControlWidgets().size());
}

TEST_F(MenuTests, connect_ContainsThreeControlWidget_ShouldConnectAllWidgetsToOutput)
{
    ControlConnection controlConnection { [](const WidgetCommand&) {} };
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithControlWithExpectedConnect(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedConnect(WidgetType::BUTTON));
    menu.addWidget(getMockWidgetWithControlWithExpectedConnect(WidgetType::BUTTON));

    menu.connect(controlConnection);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(3, menu.getControlWidgets().size());
}
