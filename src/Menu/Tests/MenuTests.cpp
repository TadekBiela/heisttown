#include <Menu.h>
#include <MockWidget.h>
#include <MockWidgetsFactory.h>
#include <StubWidgetsFactory.h>
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
    static auto getPreparedMenu(const MenuInitList& initList, MockWidgetGetter getMockWidget) -> MenuTestable
    {
        std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
        MenuTestable menu;

        for (const auto& init : initList)
        {
            EXPECT_CALL(*factory, create(init.first, _, init.second, _)).WillOnce(Return(ByMove(getMockWidget(init.first))));
            menu.addWidget(factory->create(init.first, {}, init.second, ""));
        }

        return menu;
    }
    static auto getMockWidgetWithExpectedShow(const WidgetType& type) -> std::unique_ptr<MockWidget>
    {
        std::unique_ptr<MockWidget> widget { getMockWidget(type) };
        EXPECT_CALL(*widget, show());
        return widget;
    }
    static auto getMockWidgetWithExpectedHide(const WidgetType& type) -> std::unique_ptr<MockWidget>
    {
        std::unique_ptr<MockWidget> widget { getMockWidget(type) };
        EXPECT_CALL(*widget, hide());
        return widget;
    }

    static auto getMockWidget(const WidgetType& type) -> std::unique_ptr<MockWidget>
    {
        std::unique_ptr<MockWidget> widget { std::make_unique<MockWidget>() };
        EXPECT_CALL(*widget, type()).WillOnce(Return(type));
        return widget;
    }
};

TEST_F(MenuTests, addWidget_ButtonWidget_ShouldAddButtonToDynamicWidgets)
{
    StubWidgetsFactory factory;
    MenuTestable menu;

    menu.addWidget(factory.create(WidgetType::BUTTON, {}, "", ""));

    ASSERT_EQ(1, menu.getDynamicWidgets().size());
    EXPECT_EQ(WidgetType::BUTTON, menu.getDynamicWidgets().at(0)->type());
    EXPECT_EQ(0, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, addWidget_LabelWidget_ShouldAddLabeToStaticWidgets)
{
    StubWidgetsFactory factory;
    MenuTestable menu;

    menu.addWidget(factory.create(WidgetType::LABEL, {}, "", ""));

    EXPECT_EQ(0, menu.getDynamicWidgets().size());
    ASSERT_EQ(1, menu.getStaticWidgets().size());
    EXPECT_EQ(WidgetType::LABEL, menu.getStaticWidgets().at(0)->type());
}

TEST_F(MenuTests, addWidget_DifferentWidgets_ShouldAddWidgetsRegardingToType)
{
    StubWidgetsFactory factory;
    MenuTestable menu;

    menu.addWidget(factory.create(WidgetType::LABEL, {}, "", ""));
    menu.addWidget(factory.create(WidgetType::BUTTON, {}, "", ""));
    menu.addWidget(factory.create(WidgetType::BUTTON, {}, "", ""));
    menu.addWidget(factory.create(WidgetType::BUTTON, {}, "", ""));
    menu.addWidget(factory.create(WidgetType::LABEL, {}, "", ""));
    menu.addWidget(factory.create(WidgetType::BUTTON, {}, "", ""));

    EXPECT_EQ(4, menu.getDynamicWidgets().size());
    EXPECT_EQ(2, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsOneStaticWidget_ShouldShowWidget)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::LABEL, "" } },
        getMockWidgetWithExpectedShow
    ) };

    menu.show();

    EXPECT_EQ(1, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeStaticWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::LABEL, "widget1" },
          { WidgetType::LABEL, "widget2" },
          { WidgetType::LABEL, "widget3" } },
        getMockWidgetWithExpectedShow
    ) };

    menu.show();

    EXPECT_EQ(3, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsOneDynamicWidget_ShouldShowWidget)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::BUTTON, "" } },
        getMockWidgetWithExpectedShow
    ) };

    menu.show();

    EXPECT_EQ(1, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeDynamicWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::BUTTON, "widget1" },
          { WidgetType::BUTTON, "widget2" },
          { WidgetType::BUTTON, "widget3" } },
        getMockWidgetWithExpectedShow
    ) };

    menu.show();

    EXPECT_EQ(3, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, show_ContainsTwoStaticAndDynamicWidgets_ShouldShowAllWidgets)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::LABEL, "widget1" },
          { WidgetType::LABEL, "widget2" },
          { WidgetType::BUTTON, "widget3" },
          { WidgetType::BUTTON, "widget4" } },
        getMockWidgetWithExpectedShow
    ) };

    menu.show();

    EXPECT_EQ(2, menu.getStaticWidgets().size());
    EXPECT_EQ(2, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, hide_ContainsOneStaticWidget_ShouldHideWidget)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::LABEL, "" } },
        getMockWidgetWithExpectedHide
    ) };

    menu.hide();

    EXPECT_EQ(1, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, hide_ContainsThreeStaticWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::LABEL, "widget1" },
          { WidgetType::LABEL, "widget2" },
          { WidgetType::LABEL, "widget3" } },
        getMockWidgetWithExpectedHide
    ) };

    menu.hide();

    EXPECT_EQ(3, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, hide_ContainsOneDynamicWidget_ShouldHideWidget)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::BUTTON, "" } },
        getMockWidgetWithExpectedHide
    ) };

    menu.hide();

    EXPECT_EQ(1, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, hide_ContainsThreeDynamicWidgets_ShouldHideAllWidgets)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::BUTTON, "widget1" },
          { WidgetType::BUTTON, "widget2" },
          { WidgetType::BUTTON, "widget3" } },
        getMockWidgetWithExpectedHide
    ) };

    menu.hide();

    EXPECT_EQ(3, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, hide_ContainsTwoStaticAndDynamicWidgets_ShouldShoHideAllWidgets)
{
    MenuTestable menu { getPreparedMenu(
        { { WidgetType::LABEL, "widget1" },
          { WidgetType::LABEL, "widget2" },
          { WidgetType::BUTTON, "widget3" },
          { WidgetType::BUTTON, "widget4" } },
        getMockWidgetWithExpectedHide
    ) };

    menu.hide();

    EXPECT_EQ(2, menu.getStaticWidgets().size());
    EXPECT_EQ(2, menu.getDynamicWidgets().size());
}
