#include <Menu.hpp>
#include <MockControlWidget.hpp>
#include <MockWidget.hpp>
#include <WidgetType.hpp>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class MenuTestable : public Menu
{
public:
    [[nodiscard]] auto getControlWidgets() const -> const ControlWidgets&
    {
        return controlWidgets;
    }
    [[nodiscard]] auto getStaticWidgets() const -> const StaticWidgets&
    {
        return staticWidgets;
    }
};

using MenuInitList = std::initializer_list<std::pair<WidgetType, WidgetText>>;
using MockWidgetGetter = const std::function<std::unique_ptr<MockWidget>(const WidgetType&)>&;

class MenuTests : public Test
{
public:
    static auto getMockWidgetWithExpectedShow(const WidgetType& type) -> std::unique_ptr<MockWidget>
    {
        auto widget { getMockWidget(type) };
        EXPECT_CALL(*widget, show());
        return widget;
    }

    static auto getMockWidgetWithExpectedHide(const WidgetType& type) -> std::unique_ptr<MockWidget>
    {
        auto widget { getMockWidget(type) };
        EXPECT_CALL(*widget, hide());
        return widget;
    }

    static auto getMockWidget(const WidgetType& type) -> std::unique_ptr<MockWidget>
    {
        auto widget { std::make_unique<MockWidget>() };
        EXPECT_CALL(*widget, type()).WillRepeatedly(Return(type));
        return widget;
    }

    static auto getMockControlWidgetWithExpectedShow(const WidgetType& type) -> std::unique_ptr<MockControlWidget>
    {
        auto widget { getMockControlWidget(type) };
        EXPECT_CALL(*widget, show());
        return widget;
    }

    static auto getMockControlWidgetWithExpectedHide(const WidgetType& type) -> std::unique_ptr<MockControlWidget>
    {
        auto widget { getMockControlWidget(type) };
        EXPECT_CALL(*widget, hide());
        return widget;
    }

    static auto getMockControlWidgetWithExpectedConnect(const WidgetType& type) -> std::unique_ptr<MockControlWidget>
    {
        auto widget { getMockControlWidget(type) };
        EXPECT_CALL(*widget, connect(_));
        return widget;
    }

    static auto getMockControlWidget(const WidgetType& type) -> std::unique_ptr<MockControlWidget>
    {
        auto widget { std::make_unique<MockControlWidget>() };
        EXPECT_CALL(*widget, type()).WillRepeatedly(Return(type));
        return widget;
    }
};

TEST_F(MenuTests, addWidget_ButtonWidget_ShouldAddButtonToControlWidgets)
{
    MenuTestable menu;

    menu.addWidget(getMockControlWidget(WidgetType::BUTTON));

    ASSERT_EQ(1, menu.getControlWidgets().size());
    EXPECT_EQ(WidgetType::BUTTON, menu.getControlWidgets().at(0)->type());
    EXPECT_EQ(0, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, addWidget_LabelWidget_ShouldAddLabeToStaticWidgets)
{
    MenuTestable menu;

    menu.addWidget(getMockWidget(WidgetType::LABEL));

    EXPECT_EQ(0, menu.getControlWidgets().size());
    ASSERT_EQ(1, menu.getStaticWidgets().size());
    EXPECT_EQ(WidgetType::LABEL, menu.getStaticWidgets().at(0)->type());
}

TEST_F(MenuTests, addWidget_DifferentWidgets_ShouldAddWidgetsRegardingToType)
{
    MenuTestable menu;

    menu.addWidget(getMockWidget(WidgetType::LABEL));
    menu.addWidget(getMockControlWidget(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidget(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidget(WidgetType::BUTTON));
    menu.addWidget(getMockWidget(WidgetType::LABEL));
    menu.addWidget(getMockControlWidget(WidgetType::BUTTON));

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
    menu.addWidget(getMockControlWidgetWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(1, menu.getControlWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeControlWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockControlWidgetWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(3, menu.getControlWidgets().size());
}

TEST_F(MenuTests, show_ContainsTwoStaticAndControlWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockControlWidgetWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedShow(WidgetType::BUTTON));

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
    menu.addWidget(getMockControlWidgetWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(1, menu.getControlWidgets().size());
}

TEST_F(MenuTests, hide_ContainsThreeControlWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockControlWidgetWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(3, menu.getControlWidgets().size());
}

TEST_F(MenuTests, hide_ContainsTwoStaticAndControlWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockControlWidgetWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedHide(WidgetType::BUTTON));

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
    menu.addWidget(getMockControlWidgetWithExpectedConnect(WidgetType::BUTTON));

    menu.connect(controlConnection);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(1, menu.getControlWidgets().size());
}

TEST_F(MenuTests, connect_ContainsThreeControlWidget_ShouldConnectAllWidgetsToOutput)
{
    ControlConnection controlConnection { [](const WidgetCommand&) {} };
    MenuTestable menu;
    menu.addWidget(getMockControlWidgetWithExpectedConnect(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedConnect(WidgetType::BUTTON));
    menu.addWidget(getMockControlWidgetWithExpectedConnect(WidgetType::BUTTON));

    menu.connect(controlConnection);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(3, menu.getControlWidgets().size());
}
