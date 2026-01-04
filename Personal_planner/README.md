# Personal Planner

A console-based event management application written in C++ that allows users to schedule and organize events with automatic chronological sorting.

## Description

Personal Planner is a command-line tool for managing personal events and appointments. Users can add events with detailed information including date, time, title, and description. The application automatically sorts events chronologically and displays them in an organized format.

## Features

- **Event Creation**: Add events with complete date/time information
- **Automatic Sorting**: Events are automatically sorted by year, month, day, hour, and minute
- **Input Validation**: Comprehensive validation for all date/time fields
- **Formatted Display**: Clean, table-like output format
- **Unlimited Events**: Add as many events as needed (limited only by memory)
- **User-Friendly Interface**: Simple menu-driven operation

## Prerequisites

- C++ compiler with C++11 support (for lambda functions)
- Standard C++ Library
- Windows OS (uses `windows.h`, `conio.h`, and `system()` calls)

## How to Build

### Using g++ (MinGW on Windows)

```bash
g++ -std=c++11 personal_planner.cpp -o personal_planner.exe
```

### Using MSVC (Visual Studio)

```bash
cl /EHsc personal_planner.cpp /Fe:personal_planner.exe
```

### Using clang++ (Windows)

```bash
clang++ -std=c++11 personal_planner.cpp -o personal_planner.exe
```

## How to Run

1. Execute the program:
   ```bash
   personal_planner.exe    # Windows
   ```

2. Use the menu to interact with the planner:
   ```
   1 - add event, 2 - print all events, 3 - exit
   ```

### Adding an Event

When you select option 1, you'll be prompted to enter:

1. **Hour** (0-23): The hour of the event
   ```
   Put hour: 14
   ```

2. **Minutes** (0-59): The minute of the event
   ```
   Put minutes: 30
   ```

3. **Day** (1-31): Day of the month
   ```
   Put day: 15
   ```

4. **Month** (1-12): Month number
   ```
   Put month: 6
   ```

5. **Year** (2017-2090): Year of the event
   ```
   Put year: 2024
   ```

6. **Title** (max 15 characters): Short event name
   ```
   Put title: Meeting
   ```

7. **Description**: Detailed description (no character limit)
   ```
   Put description: Quarterly_review_meeting
   ```

### Viewing Events

Select option 2 to display all events:

```
Hour:  Date:         Title:            Description:
14:30  15/06/2024    Meeting           Quarterly_review_meeting
09:00  20/06/2024    Dentist           Regular_checkup
```

## Example Usage Session

```
1 - add event, 2 - print all events, 3 - exit  1

Put hour: 9
Put minutes: 0
Put day: 20
Put month: 6
Put year: 2024
Put title: Dentist
Put description: Regular_checkup

1 - add event, 2 - print all events, 3 - exit  2

Hour:  Date:         Title:            Description:
09:00  20/06/2024    Dentist           Regular_checkup

Press any key to continue.

1 - add event, 2 - print all events, 3 - exit  3
```

## Technical Details

### Data Structure

The application uses a `struct Event`:
```cpp
struct Event {
    int minute, hour, day, month, year;
    string name, desc;
};
```

### Sorting Algorithm

Events are sorted using C++11 lambda functions with `std::sort`:
1. First by year
2. Then by month
3. Then by day
4. Then by hour
5. Finally by minute

This ensures perfect chronological order.

### Input Validation

| Field | Valid Range | Validation Behavior |
|-------|-------------|---------------------|
| Hour | 0-23 | Repeats prompt until valid |
| Minute | 0-59 | Repeats prompt until valid |
| Day | 1-31 | Repeats prompt until valid |
| Month | 1-12 | Repeats prompt until valid |
| Year | 2017-2090 | Repeats prompt until valid |
| Title | ≤ 15 chars | Repeats if too long, pads if shorter |
| Description | Any length | No validation |

## Key Functions

### `Enter(Vector &Vec)`
- Prompts user for event details
- Validates all input fields
- Adds event to the vector

### `Print(Vector Vec)`
- Sorts events chronologically
- Formats and displays all events
- Handles empty event list case
- Adds leading zeros for single-digit values

## Learning Objectives

This project demonstrates:
- C++ STL containers (vectors)
- Structures for data organization
- Lambda functions for custom sorting
- Input validation techniques
- Formatted console output
- Menu-driven program design
- String manipulation and padding

## Known Limitations

- **Windows-only**: Uses Windows-specific headers
- **No Persistence**: Events are lost when program exits
- **Basic Date Validation**: Doesn't check for invalid dates (e.g., Feb 31)
- **Single-byte Characters**: Title padding assumes ASCII characters
- **No Event Editing**: Can't modify or delete events after creation
- **Year Range**: Limited to 2017-2090

## Potential Improvements

Future enhancements could include:

1. **File I/O**: Save/load events from a file
2. **Cross-platform**: Replace Windows-specific code
3. **Advanced Date Validation**: Check for valid month/day combinations
4. **Event Management**: Edit and delete existing events
5. **Search Feature**: Find events by title or date
6. **Reminders**: Alert for upcoming events
7. **Recurring Events**: Support for repeating events
8. **Export Options**: Export to CSV or calendar formats
9. **Color Coding**: Different colors for different event types
10. **Time Zones**: Support for different time zones

## Troubleshooting

**Problem**: "Invalid hour entered!"
- **Solution**: Enter a number between 0 and 23

**Problem**: "Entered title is too long!"
- **Solution**: Use 15 characters or fewer for the title

**Problem**: Nothing happens when viewing empty list
- **Solution**: This is expected - add events first using option 1

---

*Part of C++ Learning Projects Collection (2016-2017)*
