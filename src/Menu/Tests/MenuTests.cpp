#include <Menu.h>
#include <StubWidgetsFactory.h>
#include <WidgetType.h>
#include <gtest/gtest.h>

class MenuTests : public testing::Test
{
};

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
