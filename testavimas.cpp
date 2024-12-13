#include <gtest/gtest.h>
#include "Studentas.h"
#include <sstream>

TEST(StudentasTest, DefaultConstructorTest) {
    Studentas student;
    EXPECT_EQ(student.skaiciuotiGalutiniVidurki(), 0);
    EXPECT_EQ(student.skaiciuotiGalutiniMediana(), 0);
}

TEST(StudentasTest, ParameterizedConstructorTest) {
    std::vector<int> namuDarbai = { 8, 9, 7 };
    Studentas student("Jonas", "Jonaitis", namuDarbai, 10);

    EXPECT_EQ(student.skaiciuotiGalutiniVidurki(), 8.5);
    EXPECT_EQ(student.skaiciuotiGalutiniMediana(), 8);
}

TEST(StudentasTest, AddNamuDarbaiTest) {
    Studentas student;
    student.addNamuDarbai(10);
    student.addNamuDarbai(8);

    EXPECT_EQ(student.skaiciuotiGalutiniVidurki(), 6.0);
}

TEST(StudentasTest, GeneruotiPazymiusTest) {
    Studentas student;
    student.generuotiPazymius(5);

    EXPECT_GE(student.skaiciuotiGalutiniVidurki(), 0);
    EXPECT_LE(student.skaiciuotiGalutiniVidurki(), 10);
}

TEST(StudentasTest, OutputStreamOperatorTest) {
    std::vector<int> namuDarbai = { 8, 7, 9 };
    Studentas student("Jonas", "Jonaitis", namuDarbai, 8);

    std::stringstream ss;
    ss << student;
    std::string expected = "Jonas               Jonaitis            8.00                8.00\n";
    EXPECT_EQ(ss.str(), expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}