#include <DefaultWidgetImpl.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <WidgetControl.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
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
    sf::RenderWindow& getWindow()
    {
        return window;
    }

private:
    sf::RenderWindow window;
};

TEST_F(DefaultWidgetImplTests, constructor_DefaultBehavior_ShapeAndTextWithCorrectPositionAndSizeAndNotVisible)
{
    const WidgetGeometry expectedGeometry { 100.0, 50.0, 160.0, 30.0 };
    const WidgetText expectedText { "Test" };

    const DefaultWidgetImplTestable widget {
        expectedGeometry,
        expectedText,
        "",
        getWindow()
    };

    EXPECT_FALSE(widget.isVisible());
    const auto& resultShape { widget.getShape() };
    EXPECT_FLOAT_EQ(expectedGeometry.x, resultShape.getPosition().x);
    EXPECT_FLOAT_EQ(expectedGeometry.y, resultShape.getPosition().y);
    EXPECT_FLOAT_EQ(expectedGeometry.width, resultShape.getSize().x);
    EXPECT_FLOAT_EQ(expectedGeometry.height, resultShape.getSize().y);
    EXPECT_STREQ(expectedText.c_str(), widget.getText().c_str());
    const auto& resultTextLabel { widget.getTextLabel() };
    EXPECT_FLOAT_EQ(0.0, resultTextLabel.getOrigin().x);
    EXPECT_FLOAT_EQ(0.0, resultTextLabel.getOrigin().y);
}

TEST_F(DefaultWidgetImplTests, show_runWhenNotVisible_ChangeToVisible)
{
    DefaultWidgetImplTestable widget {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };

    widget.show();

    EXPECT_TRUE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, show_RunTwice_ChangeToVisible)
{
    DefaultWidgetImplTestable widget {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };

    widget.show();
    widget.show();

    EXPECT_TRUE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, hide_runWhenNotVisible_StillNotVisible)
{
    DefaultWidgetImplTestable widget {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };

    widget.hide();

    EXPECT_FALSE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, hide_runWhenVisible_ChangeToNotVisible)
{
    DefaultWidgetImplTestable widget {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };
    widget.show();

    widget.hide();

    EXPECT_FALSE(widget.isVisible());
}

TEST_F(DefaultWidgetImplTests, hide_runWhenVisibleTwice_ChangeToNotVisible)
{
    DefaultWidgetImplTestable widget {
        WidgetGeometry {},
        std::string {},
        std::string {},
        getWindow()
    };
    widget.show();

    widget.hide();
    widget.hide();

    EXPECT_FALSE(widget.isVisible());
}
