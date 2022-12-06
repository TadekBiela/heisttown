#include <gtest/gtest.h>
#include <QApplication>

int StartGoodleTest(int &argc, char** &argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    return StartGoodleTest(argc, argv);
}
