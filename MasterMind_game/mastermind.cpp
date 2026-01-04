#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <random>
#include <algorithm>

// Modern C++11/14 MasterMind game implementation
class MasterMind {
private:
    static constexpr int CODE_LENGTH = 4;
    static constexpr int MAX_ATTEMPTS = 10;
    static constexpr std::array<char, 6> COLORS = {'r', 'b', 'g', 'y', 'v', 'o'};
    
    std::array<char, CODE_LENGTH> secretCode;
    std::mt19937 randomEngine;
    
    void generateCode() {
        std::uniform_int_distribution<int> dist(0, COLORS.size() - 1);
        for (auto& color : secretCode) {
            color = COLORS[dist(randomEngine)];
        }
    }
    
    bool isValidColor(char c) const {
        return std::find(COLORS.begin(), COLORS.end(), c) != COLORS.end();
    }
    
    std::string getHints(const std::array<char, CODE_LENGTH>& guess) const {
        std::string hints;
        std::array<bool, CODE_LENGTH> usedSecret = {false};
        std::array<bool, CODE_LENGTH> usedGuess = {false};
        
        // First pass: exact matches
        for (size_t i = 0; i < CODE_LENGTH; ++i) {
            if (guess[i] == secretCode[i]) {
                hints += 'O';
                usedSecret[i] = true;
                usedGuess[i] = true;
            }
        }
        
        // Second pass: color matches in wrong position
        for (size_t i = 0; i < CODE_LENGTH; ++i) {
            if (!usedGuess[i]) {
                for (size_t j = 0; j < CODE_LENGTH; ++j) {
                    if (!usedSecret[j] && guess[i] == secretCode[j]) {
                        hints += 'o';
                        usedSecret[j] = true;
                        break;
                    }
                }
            }
        }
        
        // Fill remaining with dots
        while (hints.length() < CODE_LENGTH) {
            hints += '.';
        }
        
        return hints;
    }

public:
    MasterMind() : randomEngine(std::random_device{}()) {
        generateCode();
    }
    
    void displayInstructions() const {
        std::cout << "\n=== MasterMind Game ===\n";
        std::cout << "Guess the 4-color code!\n\n";
        std::cout << "Available colors:\n";
        std::cout << "  r - red\n";
        std::cout << "  b - blue\n";
        std::cout << "  g - green\n";
        std::cout << "  y - yellow\n";
        std::cout << "  v - violet\n";
        std::cout << "  o - orange\n\n";
        std::cout << "Hints:\n";
        std::cout << "  O - correct color in correct position\n";
        std::cout << "  o - correct color in wrong position\n";
        std::cout << "  . - incorrect color\n\n";
    }
    
    bool play() {
        displayInstructions();
        
        for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt) {
            std::cout << "Attempt " << attempt << "/" << MAX_ATTEMPTS << ": ";
            
            std::array<char, CODE_LENGTH> guess;
            int validInputs = 0;
            
            while (validInputs < CODE_LENGTH) {
                char c;
                std::cin >> c;
                
                if (isValidColor(c)) {
                    guess[validInputs++] = c;
                } else {
                    std::cout << "Invalid color! Try again: ";
                }
            }
            
            std::string hints = getHints(guess);
            std::cout << "Hints: " << hints << "\n";
            
            // Check if won
            if (std::all_of(hints.begin(), hints.end(), [](char h) { return h == 'O'; })) {
                std::cout << "\n🎉 Congratulations! You cracked the code in " 
                          << attempt << " attempts!\n";
                return true;
            }
            
            std::cout << "\n";
        }
        
        std::cout << "Game Over! The code was: ";
        for (char c : secretCode) {
            std::cout << c << " ";
        }
        std::cout << "\n";
        
        return false;
    }
};

int main() {
    char playAgain;
    
    do {
        MasterMind game;
        game.play();
        
        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgain;
        std::cin.ignore(); // Clear newline
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    std::cout << "Thanks for playing!\n";
    return 0;
}
