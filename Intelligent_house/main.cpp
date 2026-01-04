#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <thread>
#include <chrono>

#include "Room.h"
#include "Sched.h"
#include "Controller.h"

// Modern C++11/14 main with smart pointers and better initialization
int main() {
    constexpr int NUM_ROOMS = 5;
    
    // Use vector of unique_ptrs for better resource management (optional)
    std::vector<CAirConditioner> airConditioners(NUM_ROOMS);
    std::vector<CRoom> rooms;
    rooms.reserve(NUM_ROOMS);
    
    // Room names for better UX
    const std::array<std::string, NUM_ROOMS> roomNames = {
        "Attic", "Living room", "Bedroom", "Garage", "Cellar"
    };
    
    // Initialize rooms with different temperature change rates
    for (int i = 0; i < NUM_ROOMS; ++i) {
        float tempIncreaseRate = 0.01f * (i + 1);  // Natural heat gain
        float tempDecreaseRate = 0.1f * (i + 1);   // AC cooling rate
        rooms.emplace_back(&airConditioners[i], tempDecreaseRate, tempIncreaseRate, static_cast<short>(i));
    }
    
    // Get desired temperatures from user
    std::cout << "=== Intelligent House Climate Control ===\n\n";
    std::cout << "Set the desired temperature for each room:\n\n";
    
    std::vector<int> targetTemperatures(NUM_ROOMS);
    for (int i = 0; i < NUM_ROOMS; ++i) {
        std::cout << roomNames[i] << ": ";
        while (!(std::cin >> targetTemperatures[i]) || 
               targetTemperatures[i] < 10 || targetTemperatures[i] > 35) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid! Enter temperature (10-35°C): ";
        }
    }
    
    // Create controllers for each room
    std::vector<std::unique_ptr<CController>> controllers;
    controllers.reserve(NUM_ROOMS);
    
    for (int i = 0; i < NUM_ROOMS; ++i) {
        controllers.push_back(
            std::make_unique<CController>(&airConditioners[i], &rooms[i], targetTemperatures[i])
        );
    }
    
    // Create and start scheduler
    CSched scheduler(
        &rooms[0], controllers[0].get(),
        &rooms[1], controllers[1].get(),
        &rooms[2], controllers[2].get(),
        &rooms[3], controllers[3].get(),
        &rooms[4], controllers[4].get(),
        1000  // Run for 1000 cycles
    );
    
    std::cout << "\nStarting simulation...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    scheduler.Starter();
    
    std::cout << "\nSimulation complete!\n";
    return 0;
}
