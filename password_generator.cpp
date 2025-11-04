#include <iostream>     // For input/output operations
#include <random>      // For modern random number generation
#include <string>      // For string operations
#include <algorithm>   // For std::shuffle
#include <stdexcept>   // For std::invalid_argument

// Function to check if password meets complexity requirements
bool isPasswordStrong(const std::string& password) {
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, hasSpecial = false;

    for (char c : password) {
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }

    return (hasLower && hasUpper && hasDigit && hasSpecial);
}

// Function to generate a password of specified length
std::string generatePassword(int length) {
    // Define character sets for different types of characters
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string special = "!@#$%^&*";
    
    // Validate password length
    if (length < 8) {
        throw std::invalid_argument("Password length must be at least 8 characters");
    }

    // Setup random number generation using modern C++ facilities
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister generator
    
    // Initialize password string with capacity
    std::string password;
    password.reserve(length);

    // Ensure at least one character from each category
    password += lowercase[std::uniform_int_distribution<>(0, lowercase.length()-1)(gen)];
    password += uppercase[std::uniform_int_distribution<>(0, uppercase.length()-1)(gen)];
    password += digits[std::uniform_int_distribution<>(0, digits.length()-1)(gen)];
    password += special[std::uniform_int_distribution<>(0, special.length()-1)(gen)];

    // Combine all characters for remaining length
    std::string allChars = lowercase + uppercase + digits + special;
    std::uniform_int_distribution<> distribution(0, allChars.length()-1);

    // Fill remaining length with random characters
    for (int i = 4; i < length; i++) {
        password += allChars[distribution(gen)];
    }

    // Shuffle the password to avoid predictable character positions
    std::shuffle(password.begin(), password.end(), gen);

    return password;
}

int main() {
    try {
        // Get desired password length from user
        int length;
        std::cout << "Enter password length (minimum 8): ";
        std::cin >> length;

        // Check for valid input
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input. Please enter a number.");
        }

        // Generate and display password
        std::string password = generatePassword(length);
        std::cout << "Generated password: " << password << std::endl;
        
        // Display password strength confirmation
        std::cout << "Password meets complexity requirements: " 
                  << (isPasswordStrong(password) ? "Yes" : "No") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}