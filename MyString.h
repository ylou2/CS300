#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>

class MyString {
private:
    char* data;       // Pointer to the character array
    size_t length_;   // Length of the string

public:
    // Constructor from std::string
    MyString(const std::string& str);

    // Copy constructor
    MyString(const MyString& other);

    // Destructor
    ~MyString();

    // Method to convert MyString to std::string
    std::string toString() const;

    // Method to get the length of the string
    size_t length() const;

    // Method to get a substring
    MyString substr(size_t start, size_t n = std::string::npos) const;

    // Concatenation operator
    MyString operator+(const MyString& other) const;

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& os, const MyString& myString);

    // Index operator
    char& operator[](size_t index);

    // Comparison operators
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator>=(const MyString& other) const;

    // Assignment operator (deep copy)
    MyString& operator=(const MyString& other);
};

#endif // MYSTRING_H
