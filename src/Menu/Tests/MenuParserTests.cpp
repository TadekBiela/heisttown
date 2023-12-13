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
            "   size: " + geometry.toString() + "\n"
            "   text: " + text + "\n"
            "   style: " + style + "\n"
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
    fileLoader->setLoadedData(TextFileLoadedData { { "MainMenu", TextFile { "dummy/Path.txt", input } } });
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
    fileLoader->setLoadedData(TextFileLoadedData { { "MainMenu", TextFile { "dummy/Path.txt", input } } });
    std::unique_ptr<MockWidgetsFactory> factory { std::make_unique<MockWidgetsFactory>() };
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry1, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    EXPECT_CALL(*factory, create(WidgetType::BUTTON, expectedGeometry2, expectedText, "")).WillOnce(Return(ByMove(std::make_unique<StubWidget>())));
    MenuParser parser(std::move(factory));

    Menus result = parser.parse(std::move(fileLoader));

    ASSERT_EQ(1, result.size());
}
