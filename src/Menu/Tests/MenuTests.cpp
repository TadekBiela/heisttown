#include <Menu.h>
#include <MockWidget.h>
#include <MockWidgetsFactory.h>
#include <StubWidgetsFactory.h>
#include <WidgetType.h>
#include <gtest/gtest.h>

using namespace testing;

class MenuTests : public Test
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

TEST_F(MenuTests, show_ContainsOneStaticWidget_ShouldShowWidget)
{
    std::unique_ptr<MockWidget> widget { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget, type()).WillOnce(Return(WidgetType::LABEL));
    EXPECT_CALL(*widget, show());
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(_, _, _, _)).WillOnce(Return(ByMove(std::move(widget))));
    MenuTestable menu;
    menu.addWidget(factory->create(WidgetType::LABEL, {}, "", ""));

    menu.show();

    EXPECT_EQ(1, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeStaticWidgets_ShouldShowAllWidgets)
{
    std::unique_ptr<MockWidget> widget1 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget1, type()).WillOnce(Return(WidgetType::LABEL));
    EXPECT_CALL(*widget1, show());
    std::unique_ptr<MockWidget> widget2 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget2, type()).WillOnce(Return(WidgetType::LABEL));
    EXPECT_CALL(*widget2, show());
    std::unique_ptr<MockWidget> widget3 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget3, type()).WillOnce(Return(WidgetType::LABEL));
    EXPECT_CALL(*widget3, show());
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, _, "widget1", _)).WillOnce(Return(ByMove(std::move(widget1))));
    EXPECT_CALL(*factory, create(WidgetType::LABEL, _, "widget2", _)).WillOnce(Return(ByMove(std::move(widget2))));
    EXPECT_CALL(*factory, create(WidgetType::LABEL, _, "widget3", _)).WillOnce(Return(ByMove(std::move(widget3))));
    MenuTestable menu;
    menu.addWidget(factory->create(WidgetType::LABEL, {}, "widget1", ""));
    menu.addWidget(factory->create(WidgetType::LABEL, {}, "widget2", ""));
    menu.addWidget(factory->create(WidgetType::LABEL, {}, "widget3", ""));

    menu.show();

    EXPECT_EQ(3, menu.getStaticWidgets().size());
}

TEST_F(MenuTests, show_ContainsOneDynamicWidget_ShouldShowWidget)
{
    std::unique_ptr<MockWidget> widget { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget, type()).WillOnce(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget, show());
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(_, _, _, _)).WillOnce(Return(ByMove(std::move(widget))));
    MenuTestable menu;
    menu.addWidget(factory->create(WidgetType::BUTTON, {}, "", ""));

    menu.show();

    EXPECT_EQ(1, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, show_ContainsThreeDynamicWidgets_ShouldShowAllWidgets)
{
    std::unique_ptr<MockWidget> widget1 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget1, type()).WillOnce(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget1, show());
    std::unique_ptr<MockWidget> widget2 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget2, type()).WillOnce(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget2, show());
    std::unique_ptr<MockWidget> widget3 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget3, type()).WillOnce(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget3, show());
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, _, "widget1", _)).WillOnce(Return(ByMove(std::move(widget1))));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, _, "widget2", _)).WillOnce(Return(ByMove(std::move(widget2))));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, _, "widget3", _)).WillOnce(Return(ByMove(std::move(widget3))));
    MenuTestable menu;
    menu.addWidget(factory->create(WidgetType::BUTTON, {}, "widget1", ""));
    menu.addWidget(factory->create(WidgetType::BUTTON, {}, "widget2", ""));
    menu.addWidget(factory->create(WidgetType::BUTTON, {}, "widget3", ""));

    menu.show();

    EXPECT_EQ(3, menu.getDynamicWidgets().size());
}

TEST_F(MenuTests, show_ContainsTwoStaticAndDynamicWidgets_ShouldShowAllWidgets)
{
    std::unique_ptr<MockWidget> widget1 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget1, type()).WillOnce(Return(WidgetType::LABEL));
    EXPECT_CALL(*widget1, show());
    std::unique_ptr<MockWidget> widget2 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget2, type()).WillOnce(Return(WidgetType::LABEL));
    EXPECT_CALL(*widget2, show());
    std::unique_ptr<MockWidget> widget3 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget3, type()).WillOnce(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget3, show());
    std::unique_ptr<MockWidget> widget4 { std::make_unique<MockWidget>() };
    EXPECT_CALL(*widget4, type()).WillOnce(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget4, show());
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, _, "widget1", _)).WillOnce(Return(ByMove(std::move(widget1))));
    EXPECT_CALL(*factory, create(WidgetType::LABEL, _, "widget2", _)).WillOnce(Return(ByMove(std::move(widget2))));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, _, "widget3", _)).WillOnce(Return(ByMove(std::move(widget3))));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, _, "widget4", _)).WillOnce(Return(ByMove(std::move(widget4))));
    MenuTestable menu;
    menu.addWidget(factory->create(WidgetType::LABEL, {}, "widget1", ""));
    menu.addWidget(factory->create(WidgetType::LABEL, {}, "widget2", ""));
    menu.addWidget(factory->create(WidgetType::BUTTON, {}, "widget3", ""));
    menu.addWidget(factory->create(WidgetType::BUTTON, {}, "widget4", ""));

    menu.show();

    EXPECT_EQ(2, menu.getStaticWidgets().size());
    EXPECT_EQ(2, menu.getDynamicWidgets().size());
}
