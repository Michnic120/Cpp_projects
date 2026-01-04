#include "Sched.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#endif

CSched::CSched(CRoom* rom1, CController* cont1, CRoom* rom2, CController* cont2,
               CRoom* rom3, CController* cont3, CRoom* rom4, CController* cont4,
               CRoom* rom5, CController* cont5, int cycle)
    : iTimeCycle(cycle),
      room1(rom1), con1(cont1),
      room2(rom2), con2(cont2),
      room3(rom3), con3(cont3),
      room4(rom4), con4(cont4),
      room5(rom5), con5(cont5) {
    // C++11: Member initializer list
}

CSched::~CSched() {
    // Destructor
}

void CSched::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        std::cout << "\033[2J\033[1;1H";
    #endif
}

void CSched::Starter() {
    using namespace std::chrono_literals;  // C++14
    
    const std::array<std::string, 5> roomNames = {
        "Attic", "Living room", "Bedroom", "Garage", "Cellar"
    };
    
    std::array<CRoom*, 5> rooms = {room1, room2, room3, room4, room5};
    std::array<CController*, 5> controllers = {con1, con2, con3, con4, con5};
    
    for (int i = 0; i <= iTimeCycle; ++i) {
        clearScreen();
        
        // Display header
        std::cout << "=== Intelligent House Climate Control ===\n";
        std::cout << "Cycle: " << i << "/" << iTimeCycle << "\n\n";
        std::cout << std::left 
                  << std::setw(15) << "Room"
                  << std::setw(20) << "Current Temp (°C)"
                  << std::setw(20) << "Target Temp (°C)"
                  << "AC Status\n";
        std::cout << std::string(70, '-') << "\n";
        
        // Display room information
        for (size_t j = 0; j < rooms.size(); ++j) {
            std::cout << std::left
                      << std::setw(15) << roomNames[j]
                      << std::setw(20) << std::fixed << std::setprecision(1) 
                      << rooms[j]->GiveTem()
                      << std::setw(20) << controllers[j]->GiveTemp()
                      << (rooms[j]->cond1->GiveStatus() ? "ON" : "OFF") << "\n";
        }
        
        std::cout << "\nCommands: room+/- (e.g., attic+), roomwindow+/- (e.g., atticwindow+)\n";
        std::cout << "Available rooms: attic, livroom, bedroom, garage, cellar\n";
        
        // Update temperatures
        for (auto* room : rooms) {
            room->ChangeTem();
        }
        
        // Check for user input (non-blocking on Windows)
        #ifdef _WIN32
        if (_kbhit()) {
            std::string command;
            std::cin >> command;
            
            // Temperature controls
            if (command == "attic+") con1->IncreaseTemp();
            else if (command == "attic-") con1->DecreaseTemp();
            else if (command == "livroom+") con2->IncreaseTemp();
            else if (command == "livroom-") con2->DecreaseTemp();
            else if (command == "bedroom+") con3->IncreaseTemp();
            else if (command == "bedroom-") con3->DecreaseTemp();
            else if (command == "garage+") con4->IncreaseTemp();
            else if (command == "garage-") con4->DecreaseTemp();
            else if (command == "cellar+") con5->IncreaseTemp();
            else if (command == "cellar-") con5->DecreaseTemp();
            
            // Window controls
            else if (command == "atticwindow+") {
                room1->plus *= 1.5f;
                std::cout << "\nAttic window opened.\n";
            }
            else if (command == "atticwindow-") {
                room1->plus /= 1.5f;
                std::cout << "\nAttic window closed.\n";
            }
            else if (command == "livroomwindow+") {
                room2->plus *= 1.5f;
                std::cout << "\nLiving room window opened.\n";
            }
            else if (command == "livroomwindow-") {
                room2->plus /= 1.5f;
                std::cout << "\nLiving room window closed.\n";
            }
            else if (command == "bedroomwindow+") {
                room3->plus *= 1.5f;
                std::cout << "\nBedroom window opened.\n";
            }
            else if (command == "bedroomwindow-") {
                room3->plus /= 1.5f;
                std::cout << "\nBedroom window closed.\n";
            }
        }
        #endif
        
        // Run controllers
        for (auto* controller : controllers) {
            controller->Control();
        }
        
        // C++11: Use chrono instead of Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

