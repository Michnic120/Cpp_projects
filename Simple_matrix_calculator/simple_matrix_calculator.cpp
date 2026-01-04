#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <stdexcept>

// Modern C++11/14 Matrix Calculator with smart pointers and RAII
class Matrix {
private:
    int rows_;
    int cols_;
    std::vector<std::vector<double>> data_;
    
public:
    // C++11: Constructor with initialization
    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
        data_.resize(rows_, std::vector<double>(cols_, 0.0));
    }
    
    // Constructor that reads values from user
    Matrix(int rows, int cols, bool readInput) : Matrix(rows, cols) {
        if (readInput) {
            std::cout << "Enter " << rows_ * cols_ << " numbers for the matrix:\n";
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    while (!(std::cin >> data_[i][j])) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Invalid input! Enter a number: ";
                    }
                }
            }
        }
    }
    
    // Getters
    int rows() const { return rows_; }
    int cols() const { return cols_; }
    
    // Access operators
    double& at(int i, int j) { return data_.at(i).at(j); }
    const double& at(int i, int j) const { return data_.at(i).at(j); }
    
    // Print matrix
    void print() const {
        for (int i = 0; i < rows_; ++i) {
            std::cout << "|";
            for (int j = 0; j < cols_; ++j) {
                std::cout << std::setw(8) << std::fixed << std::setprecision(2) 
                          << data_[i][j];
                if (j + 1 != cols_) std::cout << " ";
            }
            std::cout << "|\n";
        }
    }
    
    // Addition operator (C++11)
    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have same dimensions for addition");
        }
        
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }
    
    // Subtraction operator
    Matrix operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have same dimensions for subtraction");
        }
        
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] - other.data_[i][j];
            }
        }
        return result;
    }
    
    // Multiplication operator
    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument(
                "First matrix columns must equal second matrix rows for multiplication");
        }
        
        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                double sum = 0.0;
                for (int k = 0; k < cols_; ++k) {
                    sum += data_[i][k] * other.data_[k][j];
                }
                result.data_[i][j] = sum;
            }
        }
        return result;
    }
};

class MatrixCalculator {
private:
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            std::cout << "\033[2J\033[1;1H";
        #endif
    }
    
    void waitForEnter() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }
    
    int getPositiveInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value && value > 0) {
                return value;
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Must be a positive integer.\n";
        }
    }

public:
    void run() {
        clearScreen();
        
        std::cout << "=== Matrix Calculator ===\n\n";
        std::cout << "Do you want both matrices to have the same size? (y/n): ";
        char sameSize;
        std::cin >> sameSize;
        
        int rows1, cols1, rows2, cols2;
        
        if (sameSize == 'y' || sameSize == 'Y') {
            clearScreen();
            rows1 = getPositiveInt("Enter number of rows: ");
            cols1 = getPositiveInt("Enter number of columns: ");
            rows2 = rows1;
            cols2 = cols1;
        } else {
            clearScreen();
            std::cout << "First matrix:\n";
            rows1 = getPositiveInt("  Rows: ");
            cols1 = getPositiveInt("  Columns: ");
            
            std::cout << "\nSecond matrix:\n";
            rows2 = getPositiveInt("  Rows: ");
            cols2 = getPositiveInt("  Columns: ");
            
            // Check if multiplication is possible
            if (cols1 != rows2 && cols2 != rows1) {
                std::cout << "\nError: Multiplication not possible with these dimensions!\n";
                std::cout << "For multiplication, columns of first must equal rows of second.\n";
                waitForEnter();
                return;
            }
        }
        
        try {
            clearScreen();
            std::cout << "=== Enter First Matrix ===\n";
            Matrix mat1(rows1, cols1, true);
            
            clearScreen();
            std::cout << "=== Enter Second Matrix ===\n";
            Matrix mat2(rows2, cols2, true);
            
            clearScreen();
            std::cout << "=== Matrix Calculator ===\n\n";
            std::cout << "Operations:\n";
            std::cout << "1 - Print matrices\n";
            std::cout << "2 - Multiply\n";
            if (sameSize == 'y' || sameSize == 'Y') {
                std::cout << "3 - Add\n";
                std::cout << "4 - Subtract\n";
            }
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            
            clearScreen();
            
            switch (choice) {
                case 1: {
                    std::cout << "First Matrix:\n";
                    mat1.print();
                    std::cout << "\nSecond Matrix:\n";
                    mat2.print();
                    break;
                }
                case 2: {
                    try {
                        Matrix result = mat1 * mat2;
                        std::cout << "Result of Multiplication:\n";
                        result.print();
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 3: {
                    if (sameSize != 'y' && sameSize != 'Y') {
                        std::cout << "Addition not available for different-sized matrices!\n";
                        break;
                    }
                    try {
                        Matrix result = mat1 + mat2;
                        std::cout << "Result of Addition:\n";
                        result.print();
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 4: {
                    if (sameSize != 'y' && sameSize != 'Y') {
                        std::cout << "Subtraction not available for different-sized matrices!\n";
                        break;
                    }
                    try {
                        Matrix result = mat1 - mat2;
                        std::cout << "Result of Subtraction:\n";
                        result.print();
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                default:
                    std::cout << "Invalid choice!\n";
                    break;
            }
            
            waitForEnter();
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            waitForEnter();
        }
    }
};

int main() {
    MatrixCalculator calc;
    
    char again;
    do {
        calc.run();
        
        std::cout << "\nPerform another operation? (y/n): ";
        std::cin >> again;
        std::cin.ignore(10000, '\n');
        
    } while (again == 'y' || again == 'Y');
    
    std::cout << "Goodbye!\n";
    return 0;
}
