#include <MenuController.h>
#include <MenuParser.h>
#include <MockWidget.h>
#include <MockWidgetsFactory.h>
#include <StubFileLoader.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class MenuControllerTests : public testing::Test
{
};

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
};

TEST_F(MenuControllerTests, constructor_ParserReturnEmptyMenus_ShouldDoNothing)
{
    std::unique_ptr<StubFileLoader<TextFile>> stubSource { std::make_unique<StubFileLoader<TextFile>>("") };
    std::unique_ptr<MockWidgetsFactory> widgetFactory;
    std::unique_ptr<MenuParser> stubParser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

    MenuControllerTestable controller(std::move(stubParser), std::move(stubSource));

    EXPECT_EQ(0, controller.getMenus().size());
}

TEST_F(MenuControllerTests, constructor_ParserReturnOneMenu_ShouldContainOneMenu)
{
    std::unique_ptr<StubFileLoader<TextFile>> stubSource { std::make_unique<StubFileLoader<TextFile>>("") };
    stubSource->setLoadedData({ { "MainMenu", TextFile { "", "" } } });
    std::unique_ptr<MockWidgetsFactory> widgetFactory;
    std::unique_ptr<MenuParser> stubParser { std::make_unique<MenuParser>(std::move(widgetFactory)) };

    MenuControllerTestable controller(std::move(stubParser), std::move(stubSource));

    EXPECT_EQ(1, controller.getMenus().size());
}
