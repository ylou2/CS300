#include <gtest/gtest.h>
#include "MyString.h"
/*
 * AI Tool: OpenAI ChatGPT
 * Prompt: "Create a test file using Google Test for a custom MyString class in C++. 
 * Include tests for all functions, including constructors, destructors, 
 * operators, and edge cases. Structure tests in multiple TEST functions."
 */


// Test suite for MyString class
class MyStringTest : public ::testing::Test {
protected:
    void SetUp() override {
        // This can be used to set up test conditions if needed.
    }

    void TearDown() override {
        // This can be used to clean up after tests if needed.
    }
};

// Test construction from std::string
TEST_F(MyStringTest, ConstructorFromString) {
    MyString str("Hello");
    EXPECT_EQ(str.toString(), "Hello");
    EXPECT_EQ(str.length(), 5);
}

// Test copy constructor
TEST_F(MyStringTest, CopyConstructor) {
    MyString str1("World");
    MyString str2(str1);
    EXPECT_EQ(str2.toString(), "World");
    EXPECT_EQ(str2.length(), 5);
}

// Test destructor
TEST_F(MyStringTest, Destructor) {
    {
        MyString str("Temporary");
    } // Check that it cleans up without memory leaks (use tools like Valgrind to confirm)
}

// Test substring method
TEST_F(MyStringTest, Substring) {
    MyString str("Hello World");
    EXPECT_EQ(str.substr(0, 5).toString(), "Hello");
    EXPECT_EQ(str.substr(6).toString(), "World");
    EXPECT_THROW(str.substr(20), std::invalid_argument); // Testing out of range
}

// Test concatenation operator
TEST_F(MyStringTest, ConcatenationOperator) {
    MyString str1("Hello");
    MyString str2(" World");
    MyString result = str1 + str2;
    EXPECT_EQ(result.toString(), "Hello World");
}

// Test index operator
// Test index operator
TEST_F(MyStringTest, IndexOperator) {
    MyString str("Index Test");
    EXPECT_EQ(str[0], 'I');     // Valid index
    EXPECT_EQ(str[9], 't');     // Changed from 10 to 9 to match the last character
    EXPECT_THROW(str[10], std::out_of_range); // Out of range test remains the same
}


// Test comparison operators
TEST_F(MyStringTest, ComparisonOperators) {
    MyString str1("A");
    MyString str2("B");
    EXPECT_TRUE(str1 < str2);
    EXPECT_TRUE(str1 <= str2);
    EXPECT_TRUE(str1 != str2);
    EXPECT_TRUE(str2 > str1);
    EXPECT_TRUE(str2 >= str1);
    EXPECT_FALSE(str1 == str2);
}

// Test assignment operator
TEST_F(MyStringTest, AssignmentOperator) {
    MyString str1("Original");
    MyString str2("To Be Assigned");
    str2 = str1;
    EXPECT_EQ(str2.toString(), "Original");
}

// Test empty string
TEST_F(MyStringTest, EmptyString) {
    MyString str("");
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.toString(), "");
    EXPECT_THROW(str.substr(0, 1), std::invalid_argument); // Out of range
}

// Additional tests can be added here...

// Main function for running all tests
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(output) = "/Users/louyuxin/last_test.log"; 
    return RUN_ALL_TESTS();
}


