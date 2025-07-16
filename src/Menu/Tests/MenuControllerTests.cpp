#include <IFileLoader.hpp>
#include <IMenuParser.hpp>
#include <MainControlConnector.hpp>
#include <MenuController.hpp>
#include <MenuParser.hpp>
#include <Menus.hpp>
#include <MockControlWidget.hpp>
#include <MockFileLoader.hpp>
#include <MockWidgetsFactory.hpp>
#include <TextFile.hpp>
#include <WidgetType.hpp>
#include <gmock/gmock.h>
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

    [[nodiscard]] auto getMenus() const -> const Menus&
    {
        return menus;
    }

    [[nodiscard]] auto getCurrentMenu() const -> const Menus::iterator&
    {
        return currentMenuStack.top();
    }
};

class MenuControllerTests : public Test
{
public:
    [[nodiscard]] static auto prepareMenuControllerWithMenu() -> MenuControllerTestable
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
    auto widget { std::make_unique<MockControlWidget>() };
    EXPECT_CALL(*widget, type()).WillRepeatedly(Return(WidgetType::BUTTON));
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

TEST_F(MenuControllerTests, control_SinglePlayer_ShouldSwitchCurrentMenuToSinglePlayer)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("SinglePlayer");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, control_Settings_ShouldSwitchCurrentMenuToSettings)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("Settings");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Settings"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, control_SinglePlayerNextToSettings_ShouldSwitchCurrentMenuToSettingsAnd)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("SinglePlayer");
    controller.control("Settings");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Settings"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, control_SinglePlayerAndBack_ShouldSwitchCurrentMenuToSinglePlayerAndBackToMainMenu)
{
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };

    controller.control("SinglePlayer");
    controller.control("Back");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("MainMenu"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, control_SinglePlayerAndPlay_ShouldSwitchCurrentMenuToPauseAndSendMainCommand)
{
    MainCommand result {};
    auto mainControlConnection = [&result](const MainCommand& command)
    {
        result = command;
    };
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.setMainControl(mainControlConnection);

    controller.control("SinglePlayer");
    controller.control("Play");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
    EXPECT_EQ("SinglePlayer->Play", result);
}

TEST_F(MenuControllerTests, control_SinglePlayerPlayAndPause_ShouldSwitchCurrentMenuToPause)
{
    auto mainControlConnection = [](const MainCommand&) {};
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.setMainControl(mainControlConnection);

    controller.control("SinglePlayer");
    controller.control("Play");
    controller.control("Pause");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("Pause"), controller.getCurrentMenu());
}

TEST_F(MenuControllerTests, control_SinglePlayerPlayPauseAndAbort_ShouldSwitchCurrentMenuToSinglePlayer)
{
    MainCommand result {};
    auto mainControlConnection = [&result](const MainCommand& command)
    {
        result = command;
    };
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.setMainControl(mainControlConnection);

    controller.control("SinglePlayer");
    controller.control("Play");
    controller.control("Pause");
    controller.control("Abort");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
    EXPECT_EQ("Pause->Abort", result);
}

TEST_F(MenuControllerTests, control_SinglePlayerPlayPauseAndConitnue_ShouldStayCurrentMenuAsPause)
{
    MainCommand result {};
    auto mainControlConnection = [&result](const MainCommand& command)
    {
        result = command;
    };
    MenuControllerTestable controller { prepareMenuControllerWithMenu() };
    controller.setMainControl(mainControlConnection);

    controller.control("SinglePlayer");
    controller.control("Play");
    controller.control("Pause");
    controller.control("Continue");

    EXPECT_EQ(4, controller.getMenus().size());
    EXPECT_EQ(controller.getMenus().find("SinglePlayer"), controller.getCurrentMenu());
    EXPECT_EQ("Pause->Continue", result);
}

TEST_F(MenuControllerTests, showMenu_DefaultMainMenu_ShouldShowMainMenu)
{
    const std::map<FileName, TextFile> menusFiles = { { "MainMenu", TextFile { "", "Button:\n"
                                                                                   "    geometry: 200, 150, 100, 50\n"
                                                                                   "    text: SinglePlayer\n"
                                                                                   "    style: none\n" } } };
    auto source { std::make_unique<MockFileLoader<TextFile>>() };
    EXPECT_CALL(*source, getLoadedData()).WillRepeatedly(ReturnRef(menusFiles));
    auto widget { std::make_unique<MockControlWidget>() };
    EXPECT_CALL(*widget, type()).WillRepeatedly(Return(WidgetType::BUTTON));
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
