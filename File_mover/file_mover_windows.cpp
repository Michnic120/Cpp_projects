#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#endif

namespace fs = std::filesystem;

// Windows-specific version using Windows API
#ifdef _WIN32
int moveFileWindows() {
    std::string source, destination;
    
    system("cls");
    std::cout << "Enter source file path: ";
    std::getline(std::cin, source);
    std::cout << "Enter destination path: ";
    std::getline(std::cin, destination);
    
    system("cls");
    
    try {
        if (!MoveFileA(source.c_str(), destination.c_str())) {
            throw std::system_error(GetLastError(), std::system_category());
        }
        std::cout << source << " moved successfully.\n";
        return 0;
    }
    catch (const std::system_error& e) {
        std::cerr << "Could not move " << source << "\n";
        std::cerr << "Error: " << e.what() << "\n";
        return e.code().value();
    }
}

void displayErrorWindows(int errorCode) {
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
    _getch();
}

int main() {
    int errorCode;
    do {
        errorCode = moveFileWindows();
        displayErrorWindows(errorCode);
    } while (errorCode != 0);
    
    return 0;
}
#else
// Cross-platform version using C++17 filesystem
int moveFile() {
    std::string source, destination;
    
    std::cout << "\033[2J\033[1;1H"; // ANSI clear screen
    std::cout << "Enter source file path: ";
    std::getline(std::cin, source);
    std::cout << "Enter destination path: ";
    std::getline(std::cin, destination);
    
    std::cout << "\033[2J\033[1;1H";
    
    try {
        fs::rename(source, destination);
        std::cout << source << " moved successfully.\n";
        return 0;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Could not move " << source << "\n";
        std::cerr << "Error: " << e.what() << "\n";
        return static_cast<int>(e.code().value());
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
#endif
