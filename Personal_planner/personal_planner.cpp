#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <sstream>

// Modern C++11/14 implementation with chrono for time handling
struct Event {
    int minute, hour, day, month, year;
    std::string name, desc;
    
    Event(int mi, int ho, int d, int m, int y, std::string n, std::string des)
        : minute(mi), hour(ho), day(d), month(m), year(y), 
          name(std::move(n)), desc(std::move(des)) {}
    
    // C++14 comparison operator for sorting
    bool operator<(const Event& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        if (day != other.day) return day < other.day;
        if (hour != other.hour) return hour < other.hour;
        return minute < other.minute;
    }
    
    // Convert to time_point for validation (C++11)
    bool isValid() const {
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        if (hour < 0 || hour > 23) return false;
        if (minute < 0 || minute > 59) return false;
        
        // Check days in month
        const std::vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maxDay = daysInMonth[month - 1];
        
        // Leap year check
        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeap) maxDay = 29;
        }
        
        return day <= maxDay;
    }
};

using EventVector = std::vector<Event>;

class PersonalPlanner {
private:
    EventVector events;
    
    template<typename T>
    T getValidInput(const std::string& prompt, T min, T max) {
        T value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input! ";
                continue;
            }
            
            if (value >= min && value <= max) {
                return value;
            }
            std::cout << "Value must be between " << min << " and " << max << "! ";
        }
    }
    
    std::string padOrTrim(const std::string& str, size_t length) {
        if (str.length() > length) {
            return str.substr(0, length);
        }
        return str + std::string(length - str.length(), ' ');
    }
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            std::cout << "\033[2J\033[1;1H";
        #endif
    }
    
    void waitForEnter() {
        std::cout << "Press Enter to continue...";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }

public:
    void addEvent() {
        clearScreen();
        
        auto hour = getValidInput<int>("Enter hour (0-23): ", 0, 23);
        auto minute = getValidInput<int>("Enter minutes (0-59): ", 0, 59);
        auto day = getValidInput<int>("Enter day (1-31): ", 1, 31);
        auto month = getValidInput<int>("Enter month (1-12): ", 1, 12);
        
        // Dynamic year range based on current year
        auto currentYear = 2024; // Could use chrono to get actual year
        auto year = getValidInput<int>("Enter year: ", currentYear, 2099);
        
        std::cin.ignore(10000, '\n'); // Clear input buffer
        
        std::string name;
        while (true) {
            std::cout << "Enter title (max 15 chars): ";
            std::getline(std::cin, name);
            
            if (name.empty()) {
                std::cout << "Title cannot be empty! ";
                continue;
            }
            if (name.length() <= 15) {
                name = padOrTrim(name, 15);
                break;
            }
            std::cout << "Title too long! ";
        }
        
        std::string desc;
        std::cout << "Enter description: ";
        std::getline(std::cin, desc);
        
        Event newEvent(minute, hour, day, month, year, name, desc);
        
        if (!newEvent.isValid()) {
            std::cout << "\nWarning: Invalid date entered!\n";
            waitForEnter();
            return;
        }
        
        events.push_back(std::move(newEvent));
        std::cout << "\nEvent added successfully!\n";
        waitForEnter();
    }
    
    void printAllEvents() {
        clearScreen();
        
        if (events.empty()) {
            std::cout << "No events scheduled yet!\n";
            waitForEnter();
            return;
        }
        
        // Sort events using overloaded operator<
        std::sort(events.begin(), events.end());
        
        std::cout << std::left
                  << std::setw(8) << "Time"
                  << std::setw(14) << "Date"
                  << std::setw(17) << "Title"
                  << "Description\n";
        std::cout << std::string(60, '-') << "\n";
        
        for (const auto& event : events) {
            std::ostringstream timeStr, dateStr;
            
            timeStr << std::setfill('0') << std::setw(2) << event.hour << ":"
                    << std::setfill('0') << std::setw(2) << event.minute;
            
            dateStr << std::setfill('0') << std::setw(2) << event.day << "/"
                    << std::setfill('0') << std::setw(2) << event.month << "/"
                    << event.year;
            
            std::cout << std::left
                      << std::setw(8) << timeStr.str()
                      << std::setw(14) << dateStr.str()
                      << std::setw(17) << event.name
                      << event.desc << "\n";
        }
        
        std::cout << "\n";
        waitForEnter();
    }
    
    void run() {
        int choice;
        
        do {
            clearScreen();
            std::cout << "=== Personal Planner ===\n\n";
            std::cout << "1 - Add event\n";
            std::cout << "2 - View all events\n";
            std::cout << "3 - Exit\n\n";
            std::cout << "Choice: ";
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                choice = 0;
            }
            
            switch (choice) {
                case 1:
                    addEvent();
                    break;
                case 2:
                    printAllEvents();
                    break;
                case 3:
                    std::cout << "Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice!\n";
                    waitForEnter();
                    break;
            }
        } while (choice != 3);
    }
};

int main() {
    PersonalPlanner planner;
    planner.run();
    return 0;
}
