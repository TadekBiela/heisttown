#include <Menu.h>
#include <MockDynamicWidget.h>
#include <MockWidget.h>
#include <WidgetType.h>
#include <functional>
#include <gtest/gtest.h>

using namespace testing;

class MenuTestable : public Menu
{
public:
    [[nodiscard]] auto getDynamicWidgets() const -> const DynamicWidgets&
    {
        return dynamicWidgets;
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

    static auto getMockDynamicWidgetWithExpectedShow(const WidgetType& type) -> std::unique_ptr<MockDynamicWidget>
    {
        auto widget { getMockDynamicWidget(type) };
        EXPECT_CALL(*widget, show());
        return widget;
    }

    static auto getMockDynamicWidgetWithExpectedHide(const WidgetType& type) -> std::unique_ptr<MockDynamicWidget>
    {
        auto widget { getMockDynamicWidget(type) };
        EXPECT_CALL(*widget, hide());
        return widget;
    }

    static auto getMockDynamicWidgetWithExpectedConnect(const WidgetType& type) -> std::unique_ptr<MockDynamicWidget>
    {
        auto widget { getMockDynamicWidget(type) };
        EXPECT_CALL(*widget, connect(_));
        return widget;
    }

    static auto getMockDynamicWidget(const WidgetType& type) -> std::unique_ptr<MockDynamicWidget>
    {
        auto widget { std::make_unique<MockDynamicWidget>() };
        EXPECT_CALL(*widget, type()).WillRepeatedly(Return(type));
        return widget;
    }
};

TEST_F(MenuTests, addWidget_ButtonWidget_ShouldAddButtonToDynamicWidgets)
{
    MenuTestable menu;

    menu.addWidget(getMockDynamicWidget(WidgetType::BUTTON));

    ASSERT_EQ(1, menu.getDynamicWidgets().size());
    EXPECT_EQ(WidgetType::BUTTON, menu.getDynamicWidgets().at(0)->type());
    EXPECT_EQ(0, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, addWidget_LabelWidget_ShouldAddLabeToStaticWidgets)
{
    MenuTestable menu;

    menu.addWidget(getMockWidget(WidgetType::LABEL));

    EXPECT_EQ(0, menu.getDynamicWidgets().size());
    ASSERT_EQ(1, menu.getStaticWidgets().size());
    EXPECT_EQ(WidgetType::LABEL, menu.getStaticWidgets().at(0)->type());
}

TEST_F(MenuTests, addWidget_DifferentWidgets_ShouldAddWidgetsRegardingToType)
{
    MenuTestable menu;

    menu.addWidget(getMockWidget(WidgetType::LABEL));
    menu.addWidget(getMockDynamicWidget(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidget(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidget(WidgetType::BUTTON));
    menu.addWidget(getMockWidget(WidgetType::LABEL));
    menu.addWidget(getMockDynamicWidget(WidgetType::BUTTON));

    EXPECT_EQ(4, menu.getDynamicWidgets().size());
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

TEST_F(MenuTests, show_ContainsOneDynamicWidget_ShouldShowWidget)
{
    MenuTestable menu;
    menu.addWidget(getMockDynamicWidgetWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(1, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeDynamicWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockDynamicWidgetWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(3, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, show_ContainsTwoStaticAndDynamicWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedShow(WidgetType::LABEL));
    menu.addWidget(getMockDynamicWidgetWithExpectedShow(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedShow(WidgetType::BUTTON));

    menu.show();

    EXPECT_EQ(2, menu.getStaticWidgets().size());
    EXPECT_EQ(2, menu.getDynamicWidgets().size());
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

TEST_F(MenuTests, hide_ContainsOneDynamicWidget_ShouldHideWidget)
{
    MenuTestable menu;
    menu.addWidget(getMockDynamicWidgetWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(1, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, hide_ContainsThreeDynamicWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockDynamicWidgetWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(3, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, hide_ContainsTwoStaticAndDynamicWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu;
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockWidgetWithExpectedHide(WidgetType::LABEL));
    menu.addWidget(getMockDynamicWidgetWithExpectedHide(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedHide(WidgetType::BUTTON));

    menu.hide();

    EXPECT_EQ(2, menu.getStaticWidgets().size());
    EXPECT_EQ(2, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, connect_ContainsNoWidgets_ShouldDoNothing)
{
    MenuTestable menu {};
    ConnectionOutput connection { [](const WidgetMessage&) {} };

    menu.connect(connection);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(0, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, connect_ContainsOneStaticWidget_ShouldDoNothing)
{
    MenuTestable menu;
    menu.addWidget(getMockWidget(WidgetType::LABEL));
    ConnectionOutput connection { [](const WidgetMessage&) {} };

    menu.connect(connection);

    EXPECT_EQ(1, menu.getStaticWidgets().size());
    EXPECT_EQ(0, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, connect_ContainsOneDynamicWidget_ShouldConnectWidgetToOutput)
{
    ConnectionOutput output { [](const WidgetMessage&) {} };
    MenuTestable menu;
    menu.addWidget(getMockDynamicWidgetWithExpectedConnect(WidgetType::BUTTON));

    menu.connect(output);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(1, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, connect_ContainsThreeDynamicWidget_ShouldConnectAllWidgetsToOutput)
{
    ConnectionOutput output { [](const WidgetMessage&) {} };
    MenuTestable menu;
    menu.addWidget(getMockDynamicWidgetWithExpectedConnect(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedConnect(WidgetType::BUTTON));
    menu.addWidget(getMockDynamicWidgetWithExpectedConnect(WidgetType::BUTTON));

    menu.connect(output);

    EXPECT_EQ(0, menu.getStaticWidgets().size());
    EXPECT_EQ(3, menu.getDynamicWidgets().size());
}
