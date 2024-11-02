#include "MyString.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

// Constructor from std::string
MyString::MyString(const std::string& str) {
    length_ = str.length();
    data = new char[length_ + 1]; // +1 for the null terminator
    std::strcpy(data, str.c_str());
}

// Copy constructor
MyString::MyString(const MyString& other) {
    length_ = other.length_;
    data = new char[length_ + 1];
    std::strcpy(data, other.data);
}

// Destructor
MyString::~MyString() {
    delete[] data;
}

// Method to convert MyString to std::string
std::string MyString::toString() const {
    return std::string(data);
}

// Method to get the length of the string
size_t MyString::length() const {
    return length_;
}

MyString MyString::substr(size_t start, size_t n) const {
    if (length_ == 0) { // Handle empty string case
        throw std::invalid_argument("Cannot take substring from an empty string.");
    }
    
    if (start >= length_) { // Allowing for start == length_ only for empty substring
        throw std::invalid_argument("Start index is out of range.");
    }

    size_t new_length = (n == std::string::npos) ? (length_ - start) : std::min(n, length_ - start);
    
    // Allocate memory for the substring
    char* sub_data = new char[new_length + 1]; 
    std::strncpy(sub_data, data + start, new_length);
    sub_data[new_length] = '\0'; // Null-terminate

    MyString result(sub_data); 
    delete[] sub_data; // Free temporary memory
    return result;
}

// Concatenation operator
MyString MyString::operator+(const MyString& other) const {
    size_t new_length = length_ + other.length_;
    char* new_data = new char[new_length + 1];
    std::strcpy(new_data, data);
    std::strcat(new_data, other.data);
    MyString result(new_data);
    delete[] new_data; // Free temporary memory
    return result;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const MyString& myString) {
    os << myString.data;
    return os;
}

// Index operator
char& MyString::operator[](size_t index) {
    if (index >= length_) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

// Comparison operators
bool MyString::operator==(const MyString& other) const {
    return std::strcmp(data, other.data) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator<(const MyString& other) const {
    return std::strcmp(data, other.data) < 0;
}

bool MyString::operator<=(const MyString& other) const {
    return *this < other || *this == other;
}

bool MyString::operator>(const MyString& other) const {
    return !(*this <= other);
}

bool MyString::operator>=(const MyString& other) const {
    return !(*this < other);
}

// Assignment operator (deep copy)
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) { // Self-assignment check
        delete[] data; // Free existing resource
        length_ = other.length_;
        data = new char[length_ + 1];
        std::strcpy(data, other.data);
    }
    return *this;
}
