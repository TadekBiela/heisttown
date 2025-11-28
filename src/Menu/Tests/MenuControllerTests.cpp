#include <IFileLoader.hpp>
#include <IMenuController.hpp>
#include <IMenuParser.hpp>
#include <MenuController.hpp>
#include <MenuParser.hpp>
#include <Menus.hpp>
#include <MockFileLoader.hpp>
#include <MockWidgetWithControl.hpp>
#include <MockWidgetsFactory.hpp>
#include <TextFile.hpp>
#include <WidgetType.hpp>
#include <gtest/gtest.h>
#include <map>
#include <memory>
#include <utility>

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

    [[nodiscard]] const Menus& getMenus() const
    {
        return menus;
    }

    [[nodiscard]] const Menus::iterator& getCurrentMenu() const
    {
        return currentMenuStack.top();
    }
};

class MenuControllerTests : public Test
{
public:
    [[nodiscard]] static MenuControllerTestable prepareMenuControllerWithMenu()
    {
        const std::map<FileName, TextFile> menusFiles { { "MainMenu", TextFile { "", "" } },
                                                        { "SinglePlayer", TextFile { "", "" } },
                                                        { "Pause", TextFile { "", "" } },
                                                        { "Settings", TextFile { "", "" } } };
        auto source { std::make_unique<MockFileLoader<TextFile>>() };
        EXPECT_CALL(*source, getLoadedData()).WillRepeatedly(ReturnRef(menusFiles));
        auto widgetFactory { std::make_unique<MockWidgetsFactory>() };
        auto parser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

        return { std::move(parser), std::move(source) };
    }
};

TEST_F(MenuControllerTests, constructor_ParserReturnEmptyMenus_ShouldDoNothing)
{
    const std::map<FileName, TextFile> menusFiles {};
    auto source { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*source, getLoadedData()).WillRepeatedly(ReturnRef(menusFiles));
    auto widgetFactory { std::make_unique<MockWidgetsFactory>() };
    auto stubParser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

    const MenuControllerTestable controller(std::move(stubParser), std::move(source));

    EXPECT_EQ(0, controller.getMenus().size());
}

TEST_F(MenuControllerTests, constructor_ParserReturnsOneMenuWithButton_ShouldContainsOneMenuAndConnectButton)
{
    const std::map<FileName, TextFile> menusFiles { { "MainMenu", TextFile { "", "Button:\n"
                                                                                 "    geometry: 200, 150, 100, 50\n"
                                                                                 "    text: SinglePlayer\n"
                                                                                 "    style: none\n" } } };
    auto source { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*source, getLoadedData()).WillRepeatedly(ReturnRef(menusFiles));
    auto widgetFactory { std::make_unique<MockWidgetsFactory>() };
    auto widget { std::make_shared<MockWidgetWithControl>() };
    EXPECT_CALL(*widget, getType()).WillRepeatedly(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget, connect(_));
    EXPECT_CALL(*widget, show());
    EXPECT_CALL(*widget, hide());
    EXPECT_CALL(*widgetFactory, create(_, _, _, _)).WillOnce(Return(ByMove(std::move(widget))));
    auto parser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

    const MenuControllerTestable controller(std::move(parser), std::move(source));

    EXPECT_EQ(1, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, constructor_ParserReturnsThreeMenus_ShouldContainsAllMenusWithSetCurrent)
{
    const MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, handle_SinglePlayer_ShouldSwitchCurrentMenuToSinglePlayer)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.handle("SinglePlayer");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, handle_Settings_ShouldSwitchCurrentMenuToSettings)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.handle("Settings");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Settings"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, handle_SinglePlayerNextToSettings_ShouldSwitchCurrentMenuToSettingsAnd)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.handle("SinglePlayer");
    controller.handle("Settings");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Settings"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, handle_SinglePlayerAndBack_ShouldSwitchCurrentMenuToSinglePlayerAndBackToMainMenu)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.handle("SinglePlayer");
    controller.handle("Back");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, handle_SinglePlayerAndPlay_ShouldSwitchCurrentMenuToPauseAndSendMenuCommand)
{
    MenuCommand result { MenuCommand::NoCommand };
    auto connection = [&result](const MenuCommand& command)
    {
        result = command;
    };
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.connect(connection);

    controller.handle("SinglePlayer");
    controller.handle("Play");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
    EXPECT_EQ(MenuCommand::StartSinglePlayer, result);
}

TEST_F(MenuControllerTests, handle_SinglePlayerPlayAndPause_ShouldSwitchCurrentMenuToPause)
{
    auto connection = [](const MenuCommand&) {};
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.connect(connection);

    controller.handle("SinglePlayer");
    controller.handle("Play");
    controller.handle("Pause");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Pause"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, handle_SinglePlayerPlayPauseAndAbort_ShouldSwitchCurrentMenuToSinglePlayer)
{
    MenuCommand result { MenuCommand::NoCommand };
    auto connection = [&result](const MenuCommand& command)
    {
        result = command;
    };
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.connect(connection);

    controller.handle("SinglePlayer");
    controller.handle("Play");
    controller.handle("Pause");
    controller.handle("Abort");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
    EXPECT_EQ(MenuCommand::Abort, result);
}

TEST_F(MenuControllerTests, handle_SinglePlayerPlayPauseAndConitnue_ShouldStayCurrentMenuAsPause)
{
    MenuCommand result { MenuCommand::NoCommand };
    auto connection = [&result](const MenuCommand& command)
    {
        result = command;
    };
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.connect(connection);

    controller.handle("SinglePlayer");
    controller.handle("Play");
    controller.handle("Pause");
    controller.handle("Continue");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
    EXPECT_EQ(MenuCommand::Continue, result);
}

TEST_F(MenuControllerTests, handle_WrongCommand_ShouldIgnoreCommand)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.handle("WringCommand");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, showMenu_DefaultMainMenu_ShouldShowMainMenu)
{
    const std::map<FileName, TextFile> menusFiles = { { "MainMenu", TextFile { "", "Button:\n"
                                                                                   "    geometry: 200, 150, 100, 50\n"
                                                                                   "    text: SinglePlayer\n"
                                                                                   "    style: none\n" } } };
    auto source { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*source, getLoadedData()).WillRepeatedly(ReturnRef(menusFiles));
    auto widget { std::make_shared<MockWidgetWithControl>() };
    EXPECT_CALL(*widget, getType()).WillRepeatedly(Return(WidgetType::BUTTON));
    EXPECT_CALL(*widget, connect(_));
    EXPECT_CALL(*widget, show()).Times(2);
    EXPECT_CALL(*widget, hide());
    auto widgetFactory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*widgetFactory, create(_, _, _, _)).WillOnce(Return(ByMove(std::move(widget))));
    auto parser { std::make_unique<MenuParser>(std::move(widgetFactory)) };
    MenuControllerTestable controller(std::move(parser), std::move(source));

    controller.showMenu();

    EXPECT_EQ(1, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
}
