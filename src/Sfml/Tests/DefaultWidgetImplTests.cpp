#include <DefaultWidgetImpl.hpp>
#include <SFML/Graphics/Font.hpp>
#include <WidgetControl.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class DefaultWidgetImplTestable : public DefaultWidgetImpl
{
public:
    using DefaultWidgetImpl::DefaultWidgetImpl;

    WidgetType getType() const override
    {
        return WidgetType::LABEL;
    }

    void applyStyle() override
    {
    }

    bool isVisible() const
    {
        return visible;
    }

    const sf::RectangleShape& getShape() const
    {
        return shape;
    }

    const sf::Text& getTextLabel() const
    {
        return textLabel;
    }
};

class DefaultWidgetImplTests : public Test
{
public:
    void SetUp() override
    {
        font = std::make_shared<sf::Font>();
        auto currentPath { std::filesystem::current_path() };
        currentPath = currentPath.parent_path();
        const auto fontPath { currentPath.string() + "/Font/PixelCode.ttf" };
        font->loadFromFile(fontPath);
    }

    std::shared_ptr<sf::Font> getFont()
    {
        return font;
    }

private:
    std::shared_ptr<sf::Font> font;
};

TEST_F(DefaultWidgetImplTests, constructor_DefaultBehavior_ShapeAndTextWithCorrectPositionAndSizeAndNotVisible)
{
    const WidgetGeometry expectedGeometry { 100.0, 50.0, 160.0, 30.0 };
    const WidgetText expectedText { "Test" };

    const DefaultWidgetImplTestable widget { expectedGeometry, expectedText, "", getFont() };

    EXPECT_FALSE(widget.isVisible());
    const auto& resultShape { widget.getShape() };
    EXPECT_FLOAT_EQ(expectedGeometry.x, resultShape.getPosition().x);
    EXPECT_FLOAT_EQ(expectedGeometry.y, resultShape.getPosition().y);
    EXPECT_FLOAT_EQ(expectedGeometry.width, resultShape.getSize().x);
    EXPECT_FLOAT_EQ(expectedGeometry.height, resultShape.getSize().y);
    EXPECT_STREQ(expectedText.c_str(), widget.getText().c_str());
    const auto& resultTextLabel { widget.getTextLabel() };
    EXPECT_FLOAT_EQ(38, resultTextLabel.getOrigin().x);
    EXPECT_FLOAT_EQ(18, resultTextLabel.getOrigin().y);
}

TEST_F(DefaultWidgetImplTests, show_runWhenNotVisible_ChangeToVisible)
{
    DefaultWidgetImplTestable widget { WidgetGeometry {}, std::string {}, std::string {}, getFont() };

    widget.show();

    EXPECT_TRUE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, show_RunTwice_ChangeToVisible)
{
    DefaultWidgetImplTestable widget { WidgetGeometry {}, std::string {}, std::string {}, getFont() };

    widget.show();
    widget.show();

    EXPECT_TRUE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, hide_runWhenNotVisible_StillNotVisible)
{
    DefaultWidgetImplTestable widget { WidgetGeometry {}, std::string {}, std::string {}, getFont() };

    widget.hide();

    EXPECT_FALSE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, hide_runWhenVisible_ChangeToNotVisible)
{
    DefaultWidgetImplTestable widget { WidgetGeometry {}, std::string {}, std::string {}, getFont() };
    widget.show();

    widget.hide();

    EXPECT_FALSE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, hide_runWhenVisibleTwice_ChangeToNotVisible)
{
    DefaultWidgetImplTestable widget { WidgetGeometry {}, std::string {}, std::string {}, getFont() };
    widget.show();

    widget.hide();
    widget.hide();

    EXPECT_FALSE(widget.isVisible());
}
