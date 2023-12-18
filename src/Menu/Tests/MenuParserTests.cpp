#include <MenuParser.h>
#include <MockWidgetsFactory.h>
#include <StubFileLoader.h>
#include <StubWidget.h>
#include <StubWidgetsFactory.h>
#include <TextFile.h>
#include <Widget.h>
#include <WidgetGeometry.h>
#include <WidgetType.h>
#include <gtest/gtest.h>

using namespace testing;

using StubTextFileLoader = StubFileLoader<TextFile>;
using TextFileLoadedData = std::map<FileName, TextFile>;

class MenuParserTests : public testing::Test
{
public:
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    [[nodiscard]] static auto getWidgetText(
        const std::string& type,
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) -> std::string
    {
        return std::string {
            type + ":\n"
            "    geometry: " + geometry.toString() + "\n"
            "    text: " + text + "\n"
            "    style: " + style + "\n"
        };
    }
};

TEST_F(MenuParserTests, parse_EmptyInput_ShouldReturnEmptyMenus)
{
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData {});
    std::unique_ptr<StubWidgetsFactory> factory { std::make_unique<StubWidgetsFactory>() };

    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    EXPECT_EQ(0, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneButtonOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsOneButton)
{
    const WidgetGeometry expectedGeometry { 50, 100, 120, 40 };
    std::string expectedText { "TestText" };
    std::string input = getWidgetText("Button:", expectedGeometry, expectedText, "none");
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileTwoButtonsOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsTwoButtons)
{
    const WidgetGeometry expectedGeometry1 { 50, 100, 120, 40 };
    const WidgetGeometry expectedGeometry2 { 40, 120, 120, 250 };
    std::string expectedText { "TestText" };
    std::string input {
        getWidgetText("Button:", expectedGeometry1, expectedText, "none") + "\n" +
        getWidgetText("Button:", expectedGeometry2, expectedText, "none")
    };
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry1, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry2, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneLabelOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsOneLAbel)
{
    const WidgetGeometry expectedGeometry { 300, 200, 160, 50 };
    std::string expectedText { "TestLabelText" };
    std::string input = getWidgetText("Label:", expectedGeometry, expectedText, "none");
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileTwoLabelsOnInputNoStyle_ShouldReturnMenusWithMainMenuContainsTwoLabels)
{
    const WidgetGeometry expectedGeometry1 { 50, 100, 120, 40 };
    const WidgetGeometry expectedGeometry2 { 40, 120, 120, 250 };
    std::string expected1Text { "TestLabel1Text" };
    std::string expected2Text { "TestLabel1Text" };
    std::string input {
        getWidgetText("Label:", expectedGeometry1, expected1Text, "none") + "\n" +
        getWidgetText("Label:", expectedGeometry2, expected2Text, "none")
    };
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData { { "MainMenu", TextFile { "dummy/path/MainMenu.txt", input } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry1, expected1Text, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry2, expected2Text, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneButtonOnInputOneStyle_ShouldReturnMenusWithMainMenuContainsOneButtonWithStyle)
{
    const WidgetGeometry expectedGeometry { 50, 100, 120, 40 };
    std::string expectedText { "TestText" };
    std::string expectedStyle {
        "border-width:2px;"
        "border-style:solid;"
        "border-color:#FFFFFF;"
        "border-radius:5px;"
        "color:#FFFFFF;"
        "background-color:transparent;"
        "font-size:20px;"
    };
    std::string inputStyles {
        "@Buttons:\n"
        "    border-width: 2px;\n"
        "    border-style: solid;\n"
        "    border-color: #FFFFFF;\n"
        "    border-radius: 5px;\n"
        "    color: #FFFFFF;\n"
        "    background-color: transparent;\n"
        "    font-size: 20px;\n"
    };
    std::string inputMainMenu {
        getWidgetText("Button:", expectedGeometry, expectedText, "Buttons")
    };
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData { { "Styles", TextFile { "dummy/path/Styles.txt", inputStyles } },
                                                   { "MainMenu", TextFile { "dummy/path/MainMenu.txt", inputMainMenu } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedText, expectedStyle)).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileOneLabelOnInputOneStyle_ShouldReturnMenusWithMainMenuContainsOneLabelWithStyle)
{
    const WidgetGeometry expectedGeometry { 50, 100, 120, 40 };
    std::string expectedText { "TestText" };
    std::string expectedStyle {
        "border-width:2px;"
        "border-style:solid;"
        "border-color:#FFFFFF;"
        "border-radius:5px;"
        "color:#FFFFFF;"
        "background-color:transparent;"
        "font-size:20px;"
    };
    std::string inputStyles {
        "@Labels:\n"
        "    border-width: 2px;\n"
        "    border-style: solid;\n"
        "    border-color: #FFFFFF;\n"
        "    border-radius: 5px;\n"
        "    color: #FFFFFF;\n"
        "    background-color: transparent;\n"
        "    font-size: 20px;\n"
    };
    std::string inputMainMenu {
        getWidgetText("Label:", expectedGeometry, expectedText, "Labels")
    };
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData { { "Styles", TextFile { "dummy/path/Styles.txt", inputStyles } },
                                                   { "MainMenu", TextFile { "dummy/path/MainMenu.txt", inputMainMenu } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedText, expectedStyle)).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}

TEST_F(MenuParserTests, parse_MainMenuFileTwoLabelsAndThreeButtonsOnInputTwoStyles_ShouldReturnMenusWithMainMenuContainsAllWidgetsWithProperStyles)
{
    const WidgetGeometry expectedGeometry { 50, 100, 120, 40 };
    std::string expectedButtonsText { "ButtonTestText" };
    std::string expectedButtonsStyle {
        "border-width:2px;"
        "border-style:solid;"
        "border-radius:5px;"
        "color:#FFFFFF;"
        "font-size:10px;"
    };
    std::string expectedButtonsStyle2 {
        "border-width:5px;"
    };
    std::string expectedLabelsText { "LabelTestText" };
    std::string expectedLabelsStyle {
        "border-width:1px;"
        "border-color:#FFFFFF;"
        "font-size:25px;"
    };
    std::string inputStyles {
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
    std::string inputMainMenu {
        getWidgetText("Label:", expectedGeometry, expectedLabelsText, "Labels") + "\n" +
        getWidgetText("Button:", expectedGeometry, expectedButtonsText, "Buttons") + "\n" +
        getWidgetText("Button:", expectedGeometry, expectedButtonsText, "none") + "\n" +
        getWidgetText("Label:", expectedGeometry, expectedLabelsText, "none") + "\n" +
        getWidgetText("Button:", expectedGeometry, expectedButtonsText, "Buttons-New")
    };
    auto fileLoader { std::make_unique<StubTextFileLoader>(std::filesystem::path()) };
    fileLoader->setLoadedData(TextFileLoadedData { { "Styles", TextFile { "dummy/path/Styles.txt", inputStyles } },
                                                   { "MainMenu", TextFile { "dummy/path/MainMenu.txt", inputMainMenu } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedLabelsText, expectedLabelsStyle)).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedButtonsText, expectedButtonsStyle)).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedButtonsText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::LABEL, expectedGeometry, expectedLabelsText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry, expectedButtonsText, expectedButtonsStyle2)).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}
