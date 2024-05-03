#include <MenuController.h>
#include <MenuParser.h>
#include <MockControlWidget.h>
#include <MockWidget.h>
#include <MockWidgetsFactory.h>
#include <StubFileLoader.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class MenuControllerTestable : public MenuController
{
public:
    MenuControllerTestable(
        std::unique_ptr<IMenuParser> parser,
        std::unique_ptr<IFileLoader<TextFile>> source
    )
        : MenuController(
              std::move(parser),
              std::move(source)
          )
    {
    }

    [[nodiscard]] auto getMenus() const -> const Menus&
    {
        return menus;
    }

    [[nodiscard]] auto getCurrentMenu() const -> const Menus::iterator&
    {
        return currentMenu;
    }

    [[nodiscard]] auto getPreviousMenu() const -> const Menus::iterator&
    {
        return previousMenu;
    }
};

class MenuControllerTests : public testing::Test
{
public:
    static auto prepareMenuControllerWithMenu() -> MenuControllerTestable
    {
        auto stubSource { std::make_unique<StubFileLoader<TextFile>>("") };
        stubSource->setLoadedData({ { "MainMenu", TextFile { "", "" } },
                                    { "SinglePlayer", TextFile { "", "" } },
                                    { "Settings", TextFile { "", "" } } });
        auto widgetFactory { std::make_unique<MockWidgetsFactory>() };
        auto widget { std::make_unique<MockControlWidget>() };
        auto parser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

        return { std::move(parser), std::move(stubSource) };
    }
};

TEST_F(MenuControllerTests, constructor_ParserReturnEmptyMenus_ShouldDoNothing)
{
    auto stubSource { std::make_unique<StubFileLoader<TextFile>>("") };
    auto widgetFactory { std::make_unique<MockWidgetsFactory>() };
    auto stubParser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

    MenuControllerTestable controller(std::move(stubParser), std::move(stubSource));

    EXPECT_EQ(0, controller.getMenus().size());
}

TEST_F(MenuControllerTests, constructor_ParserReturnsOneMenuWithButton_ShouldContainsOneMenuAndConnectButton)
{
    auto stubSource { std::make_unique<StubFileLoader<TextFile>>("") };
    stubSource->setLoadedData({ { "MainMenu", TextFile { "", "Button:\n"
                                                             "    geometry: 200, 150, 100, 50\n"
                                                             "    text: SinglePlayer\n"
                                                             "    style: none\n" } } });
    auto widgetFactory { std::make_unique<MockWidgetsFactory>() };
    auto widget { std::make_unique<MockControlWidget>() };
    EXPECT_CALL(*widget, type()).WillRepeatedly(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget, connect(_));
    EXPECT_CALL(*widget, show());
    EXPECT_CALL(*widgetFactory, create(_, _, _, _)).WillOnce(Return(ByMove(std::move(widget))));
    auto parser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

    MenuControllerTestable controller(std::move(parser), std::move(stubSource));

    EXPECT_EQ(1, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getPreviousMenu());
}

TEST_F(MenuControllerTests, constructor_ParserReturnsThreeMenus_ShouldContainsAllMenusWithSetCurrentAndPrevMenuAsFirstOne)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    EXPECT_EQ(3, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getPreviousMenu());
}

TEST_F(MenuControllerTests, control_SinglePlayer_ShouldSwitchCurrentMenuToSinglePlayer)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("SinglePlayer");

    EXPECT_EQ(3, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getPreviousMenu());
}

TEST_F(MenuControllerTests, control_Settings_ShouldSwitchCurrentMenuToSettings)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("Settings");

    EXPECT_EQ(3, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Settings"), controller.getCurrentMenu());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getPreviousMenu());
}

TEST_F(MenuControllerTests, control_SinglePlayerNextToSettings_ShouldSwitchCurrentMenuToSettingsAndPrevToSinglePlayer)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("SinglePlayer");
    controller.control("Settings");

    EXPECT_EQ(3, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Settings"), controller.getCurrentMenu());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getPreviousMenu());
}

TEST_F(MenuControllerTests, control_SinglePlayerAndBack_ShouldSwitchCurrentMenuToSinglePlayerAndBackToMainMenu)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("SinglePlayer");
    controller.control("Back");

    EXPECT_EQ(3, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getPreviousMenu());
}
