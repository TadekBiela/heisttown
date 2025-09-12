#include <IFileLoader.hpp>
#include <MenuParser.hpp>
#include <Menus.hpp>
#include <MockFileLoader.hpp>
#include <MockWidget.hpp>
#include <MockWidgetsFactory.hpp>
#include <TextFile.hpp>
#include <Widget.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <map>
#include <memory>
#include <string>
#include <utility>

using namespace testing;

using MockTextFileLoader = MockFileLoader<TextFile>;
using TextFileLoadedData = std::map<FileName, TextFile>;

class MenuParserTests : public testing::Test
{
public:
    [[nodiscard]] static auto getWidgetText(
        const std::string& type,
        const WidgetGeometry& geometry = { 0.0, 0.0, 0.0, 0.0 },
        const WidgetText& text = "",
        const WidgetStyle& style = "none"
    ) -> std::string
    {
        return std::string {
            type + ":\n" +
            "    geometry: " + geometry.toString() + "\n" +
            "    text: " + text + "\n" +
            "    style: " + style + "\n"
        };
    }
};

TEST_F(MenuParserTests, parse_EmptyInput_ShouldReturnEmptyMenus)
{
    const TextFileLoadedData emptyFileContent {};
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(emptyFileContent));
    auto factory { std::make_unique<MockWidgetsFactory>() };

    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    EXPECT_EQ(0, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneButtonOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsOneButton)
{
    const WidgetGeometry expectedGeometry { 50.0, 100.0, 120.0, 40.0 };
    const std::string expectedText { "TestText" };
    const std::string input = getWidgetText("Button:", expectedGeometry, expectedText, "none");
    const TextFileLoadedData mainMenuContent { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(mainMenuContent));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileTwoButtonsOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsTwoButtons)
{
    const WidgetGeometry expectedGeometry1 { 50.0, 100.0, 120.0, 40.0 };
    const WidgetGeometry expectedGeometry2 { 40.0, 120.0, 120.0, 250.0 };
    const std::string expectedText { "TestText" };
    const std::string input {
        getWidgetText("Button:", expectedGeometry1, expectedText, "none") + "\n" +
        getWidgetText("Button:", expectedGeometry2, expectedText, "none")
    };
    const TextFileLoadedData mainMenuContent { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(mainMenuContent));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry1, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry2, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneLabelOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsOneLAbel)
{
    const WidgetGeometry expectedGeometry { 300.0, 200.0, 160.0, 50.0 };
    const std::string expectedText { "TestLabelText" };
    const std::string input = getWidgetText("Label:", expectedGeometry, expectedText, "none");
    const TextFileLoadedData mainMenuContent { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(mainMenuContent));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileTwoLabelsOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsTwoLabels)
{
    const WidgetGeometry expectedGeometry1 { 50.0, 100.0, 120.0, 40.0 };
    const WidgetGeometry expectedGeometry2 { 40.0, 120.0, 120.0, 250.0 };
    const std::string expected1Text { "TestLabel1Text" };
    const std::string expected2Text { "TestLabel1Text" };
    const std::string input {
        getWidgetText("Label:", expectedGeometry1, expected1Text, "none") + "\n" +
        getWidgetText("Label:", expectedGeometry2, expected2Text, "none")
    };
    const TextFileLoadedData mainMenuContent { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(mainMenuContent));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry1, expected1Text, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry2, expected2Text, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneButtonOnInputOneStyle_ShouldReturnMenusWithMainMenuContainsOneButtonWithStyle)
{
    const WidgetGeometry expectedGeometry { 50.0, 100.0, 120.0, 40.0 };
    const std::string expectedText { "TestText" };
    const std::string expectedStyle {
        "border-width:2px;"
        "border-style:solid;"
        "border-color:#FFFFFF;"
        "border-radius:5px;"
        "color:#FFFFFF;"
        "background-color:transparent;"
        "font-size:20px;"
    };
    const std::string inputStyles {
        "@Buttons:\n"
        "    border-width: 2px;\n"
        "    border-style: solid;\n"
        "    border-color: #FFFFFF;\n"
        "    border-radius: 5px;\n"
        "    color: #FFFFFF;\n"
        "    background-color: transparent;\n"
        "    font-size: 20px;\n"
    };
    const std::string inputMainMenu {
        getWidgetText("Button:", expectedGeometry, expectedText, "Buttons")
    };
    const TextFileLoadedData mainMenuContentWithStyles {
        { "Styles", TextFile { "dummy/path/Styles.txt", inputStyles } },
        { "MainMenu", TextFile { "dummy/path/MainMenu.txt", inputMainMenu } }
    };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(mainMenuContentWithStyles));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedText, expectedStyle)).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneLabelOnInputOneStyle_ShouldReturnMenusWithMainMenuContainsOneLabelWithStyle)
{
    const WidgetGeometry expectedGeometry { 50.0, 100.0, 120.0, 40.0 };
    const std::string expectedText { "TestText" };
    const std::string expectedStyle {
        "border-width:2px;"
        "border-style:solid;"
        "border-color:#FFFFFF;"
        "border-radius:5px;"
        "color:#FFFFFF;"
        "background-color:transparent;"
        "font-size:20px;"
    };
    const std::string inputStyles {
        "@Labels:\n"
        "    border-width: 2px;\n"
        "    border-style: solid;\n"
        "    border-color: #FFFFFF;\n"
        "    border-radius: 5px;\n"
        "    color: #FFFFFF;\n"
        "    background-color: transparent;\n"
        "    font-size: 20px;\n"
    };
    const std::string inputMainMenu {
        getWidgetText("Label:", expectedGeometry, expectedText, "Labels")
    };
    const TextFileLoadedData mainMenuContentWithStyles {
        { "Styles", TextFile { "dummy/path/Styles.txt", inputStyles } },
        { "MainMenu", TextFile { "dummy/path/MainMenu.txt", inputMainMenu } }
    };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(mainMenuContentWithStyles));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedText, expectedStyle)).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileTwoLabelsAndThreeButtonsOnInputTwoStyles_ShouldReturnMenusWithMainMenuContainsAllWidgetsWithProperStyles)
{
    const WidgetGeometry expectedGeometry { 50.0, 100.0, 120.0, 40.0 };
    const std::string expectedButtonsText { "ButtonTestText" };
    const std::string expectedButtonsStyle {
        "border-width:2px;"
        "border-style:solid;"
        "border-radius:5px;"
        "color:#FFFFFF;"
        "font-size:10px;"
    };
    const std::string expectedButtonsStyle2 {
        "border-width:5px;"
    };
    const std::string expectedLabelsText { "LabelTestText" };
    const std::string expectedLabelsStyle {
        "border-width:1px;"
        "border-color:#FFFFFF;"
        "font-size:25px;"
    };
    const std::string inputStyles {
        "@Labels:\n"
        "    border-width: 1px;\n"
        "    border-color: #FFFFFF;\n"
        "    font-size: 25px;\n"
        "@Buttons:\n"
        "    border-width: 2px;\n"
        "    border-style: solid;\n"
        "    border-radius: 5px;\n"
        "    color: #FFFFFF;\n"
        "    font-size: 10px;\n"
        "@Buttons-New:\n"
        "    border-width: 5px;\n"
    };
    const std::string inputMainMenu {
        getWidgetText("Label:", expectedGeometry, expectedLabelsText, "Labels") + "\n" +
        getWidgetText("Button:", expectedGeometry, expectedButtonsText, "Buttons") + "\n" +
        getWidgetText("Button:", expectedGeometry, expectedButtonsText, "none") + "\n" +
        getWidgetText("Label:", expectedGeometry, expectedLabelsText, "none") + "\n" +
        getWidgetText("Button:", expectedGeometry, expectedButtonsText, "Buttons-New")
    };
    const TextFileLoadedData mainMenuContentWithStyles {
        { "Styles", TextFile { "dummy/path/Styles.txt", inputStyles } },
        { "MainMenu", TextFile { "dummy/path/MainMenu.txt", inputMainMenu } }
    };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(mainMenuContentWithStyles));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedLabelsText, expectedLabelsStyle)).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedButtonsText, expectedButtonsStyle)).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedButtonsText, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedLabelsText, "")).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedButtonsText, expectedButtonsStyle2)).WillOnce(Return(ByMove(std::make_unique<MockWidget>())));
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_TwoFilesWithoutWidgetsNoStyle_ShouldReturnMenusWithTwoEmptyMenus)
{
    const TextFileLoadedData menusContent {
        { "MainMenu", TextFile { "dummy/path/MainMenu.txt", "" } },
        { "SinglePlayer", TextFile { "dummy/path/SinglePlayer.txt", "" } }
    };
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(menusContent));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(2, result.size());
}

TEST_F(MenuParserTests, parse_TwoFilesWithWidgetsNoStyle_ShouldReturnMenusWithTwoFilledMenus)
{
    auto fileLoader { std::make_unique<MockTextFileLoader>() };
    const TextFileLoadedData menusContent {
        { "MainMenu", TextFile { "dummy/path/MainMenu.txt", getWidgetText("Label") + getWidgetText("Button") + getWidgetText("Button") } },
        { "SinglePlayer", TextFile { "dummy/path/SinglePlayer.txt", getWidgetText("Button") + getWidgetText("Button") } }
    };
    EXPECT_CALL(*fileLoader, getLoadedData()).WillOnce(ReturnRef(menusContent));
    auto factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(_, _, _, _)).WillRepeatedly(DoDefault());
    MenuParser parser(std::move(factory));

    const Menus result { parser.parse(std::move(fileLoader)) };

    ASSERT_EQ(2, result.size());
}
