#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;

// Modern C++17 version with cross-platform support
int moveFile() {
    std::string source, destination;
    
    std::cout << "\033[2J\033[1;1H"; // ANSI clear screen (cross-platform)
    std::cout << "Enter source file path: ";
    std::getline(std::cin, source);
    std::cout << "Enter destination path: ";
    std::getline(std::cin, destination);
    
    std::cout << "\033[2J\033[1;1H"; // Clear screen
    
    try {
        // C++17 filesystem rename/move
        fs::rename(source, destination);
        std::cout << source << " moved successfully.\n";
        return 0;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Could not move " << source << "\n";
        std::cerr << "Error: " << e.what() << "\n";
        return static_cast<int>(e.code().value());
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return -1;
    }
}

void displayError(int errorCode) {
    switch (errorCode) {
        case 0:
            break;
        case 2:
            std::cout << "File not found. Try again.\n";
            break;
        default:
            std::cout << "Error code: " << errorCode << ". Try again.\n";
            break;
    }
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    int errorCode;
    do {
        errorCode = moveFile();
        displayError(errorCode);
    } while (errorCode != 0);
    
    return 0;
}
