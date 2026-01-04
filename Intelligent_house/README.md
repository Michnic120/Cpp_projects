# Intelligent House Climate Control Simulator

An object-oriented C++ simulation of a smart home climate control system featuring multiple rooms with independent temperature management and air conditioning control.

## Description

This project simulates an intelligent house with five rooms, each equipped with temperature sensors and air conditioning units. The system monitors room temperatures in real-time and automatically adjusts air conditioning to maintain desired temperature setpoints. Users can interact with the system to change temperature settings and open/close windows.

## Architecture

The system follows object-oriented design principles with the following class structure:

### Classes

#### `CAirConditioner`
- Manages air conditioner on/off state
- Provides status reporting
- Methods: `SetAirConditionerON()`, `SetAirConditionerOFF()`, `GiveStatus()`

#### `CRoom`
- Represents a room with temperature dynamics
- Tracks temperature changes based on AC status and environmental factors
- Contains temperature increase/decrease rates
- Methods: `ChangeTem()`, `GiveTem()`

#### `CController`
- Controls temperature management for a room
- Maintains setpoint temperature
- Implements hysteresis control (±0.5°C deadband)
- Methods: `SetTemp()`, `IncreaseTemp()`, `DecreaseTemp()`, `Control()`

#### `CThermometer`
- Represents temperature sensing capability
- Initializes at 18°C default temperature

#### `CSched`
- Main scheduler coordinating all rooms and controllers
- Updates system state at regular intervals (500ms)
- Displays current status
- Handles user input for temperature adjustments

## Features

- **5 Independent Rooms**: Attic, Living Room, Bedroom, Garage, Cellar
- **Real-time Temperature Simulation**: Dynamic temperature changes
- **Automatic Climate Control**: PID-like controller with hysteresis
- **User Interaction**: Adjust temperatures and window states during simulation
- **Visual Feedback**: Console display showing current vs. setpoint temperatures

## Prerequisites

- Windows Operating System (uses Windows API for `Sleep()` and `system()`)
- C++ compiler with C++11 support
- Windows SDK

## How to Build

### Using MSVC (Visual Studio)

```bash
cl /EHsc main.cpp AirConditioner.cpp Controller.cpp Room.cpp Sched.cpp Thermometer.cpp /Fe:intelligent_house.exe
```

### Using MinGW

```bash
g++ -std=c++11 main.cpp AirConditioner.cpp Controller.cpp Room.cpp Sched.cpp Thermometer.cpp -o intelligent_house.exe
```

### Using CMake (Recommended)

Create a `CMakeLists.txt` file:

```cmake
cmake_minimum_required(VERSION 3.10)
project(IntelligentHouse)

set(CMAKE_CXX_STANDARD 11)

add_executable(intelligent_house
    main.cpp
    AirConditioner.cpp
    Controller.cpp
    Room.cpp
    Sched.cpp
    Thermometer.cpp
)
```

Then build:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## How to Run

1. Run the executable:
   ```bash
   intelligent_house.exe
   ```

2. Set initial temperatures for each room when prompted:
   ```
   Set the temperature in every room
   
   Attic: 22
   Living room: 20
   Bed room: 19
   Garage: 15
   Cellar: 16
   ```

3. The simulation will start showing real-time updates:
   ```
              Current temperature:       Temperature on controller:
   Attic:                             18.0                                  22
   Living room:                       18.0                                  20
   ...
   ```

4. During simulation, you can adjust settings by typing commands:

### Control Commands

| Command | Description |
|---------|-------------|
| `attic+` | Increase attic temperature setpoint |
| `attic-` | Decrease attic temperature setpoint |
| `livroom+` | Increase living room temperature |
| `livroom-` | Decrease living room temperature |
| `bedroom+` | Increase bedroom temperature |
| `bedroom-` | Decrease bedroom temperature |
| `garage+` | Increase garage temperature |
| `garage-` | Decrease garage temperature |
| `cellar+` | Increase cellar temperature |
| `cellar-` | Decrease cellar temperature |
| `atticwindow+` | Open attic window (faster temperature change) |
| `atticwindow-` | Close attic window |
| `livroomwindow+` | Open living room window |
| `livroomwindow-` | Close living room window |
| `bedroomwindow+` | Open bedroom window |
| `bedroomwindow-` | Close bedroom window |

## Technical Details

### Temperature Control Algorithm

The system uses a simple bang-bang controller with hysteresis:
- If room temperature < (setpoint - 0.5°C): Turn AC OFF
- If room temperature > (setpoint + 0.5°C): Turn AC ON
- Otherwise: Maintain current state

### Temperature Dynamics

Each room has:
- **Plus factor**: Natural temperature increase rate (environmental heat gain)
- **Minus factor**: AC cooling rate
- Window opening multiplies the plus factor by 1.5

### Update Cycle

- Updates every 500ms (configurable in `CSched` constructor)
- Screen clears and refreshes each cycle
- Runs for 1000 cycles by default

## Design Patterns

This project demonstrates:
- **Composition**: Rooms contain AirConditioner objects
- **Association**: Controllers reference Rooms and AirConditioners
- **Coordinator Pattern**: CSched orchestrates all components
- **Encapsulation**: Private member variables with public accessors

## Learning Objectives

- Object-oriented programming in C++
- Class design and relationships
- Pointer management
- Real-time simulation
- Control systems basics
- User input handling

## Known Limitations

- Windows-specific (uses Windows API)
- Console-based interface only
- Simplified temperature physics model
- No file persistence
- Fixed number of rooms (5)

## Future Improvements

- Cross-platform support using C++11 `<thread>` and `<chrono>`
- Configuration file for initial settings
- Data logging and visualization
- More sophisticated PID control
- Energy consumption tracking
- Scheduling (night/day temperature profiles)
- GUI interface

---

*Part of C++ Learning Projects Collection (2016-2017)*
