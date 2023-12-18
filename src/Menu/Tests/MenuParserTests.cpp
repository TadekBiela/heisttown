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

    [[nodiscard]] static auto getButtonText(
        const WidgetGeometry& geometry,
        const WidgetText& text,
        const WidgetStyle& style
    ) -> std::string
    {
        return std::string {
            "Button:\n"
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
    std::string input = getButtonText(expectedGeometry, expectedText, "none");
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
        getButtonText(expectedGeometry1, expectedText, "none") + "\n" +
        getButtonText(expectedGeometry2, expectedText, "none")
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
        getButtonText(expectedGeometry, expectedText, "Buttons")
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
