#include <QApplication>
#include <gtest/gtest.h>

auto StartGoodleTest(int& argc, char**& argv) -> int
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

auto main(int argc, char** argv) -> int
{
    QApplication app(argc, argv);
    return StartGoodleTest(argc, argv);
}
