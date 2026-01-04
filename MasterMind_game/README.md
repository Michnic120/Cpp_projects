# MasterMind Game

A console-based C++ implementation of the classic MasterMind code-breaking game where players attempt to guess a secret color combination.

## Description

MasterMind is a logic puzzle game where the computer generates a secret code of 4 colors, and the player has 10 attempts to guess the correct combination. After each guess, the game provides hints:
- **'O' (capital)**: Correct color in the correct position
- **'o' (lowercase)**: Correct color in the wrong position
- **'.'**: Color not in the code

## Game Rules

1. The secret code consists of 4 colors
2. Available colors: Red (r), Blue (b), Green (g), Yellow (y), Violet (v), Orange (o)
3. Colors can repeat in the code
4. You have 10 attempts to guess the code
5. After each guess, you receive hints about your guess
6. Win by getting all 4 colors in correct positions (4 × 'O')

## Features

- **Random Code Generation**: Uses C++ random number generation
- **Input Validation**: Only accepts valid color codes
- **Hint System**: Provides feedback after each guess
- **Turn Counter**: Limited to 10 attempts
- **Clear Instructions**: User-friendly color key display

## Prerequisites

- C++ compiler with C++11 support
- Standard C++ library

## How to Build

### Using g++

```bash
g++ -std=c++11 mastermind.cpp -o mastermind
```

### Using clang++

```bash
clang++ -std=c++11 mastermind.cpp -o mastermind
```

### Using MSVC

```bash
cl /EHsc mastermind.cpp /Fe:mastermind.exe
```

## How to Run

1. Execute the program:
   ```bash
   ./mastermind        # Linux/Mac
   mastermind.exe      # Windows
   ```

2. Read the color key:
   ```
   Enter the color
   r - red
   b - blue
   g - green
   y - yellow
   v - violet
   o - orange
   ```

3. Enter 4 color codes (one at a time):
   ```
   r
   b
   g
   y
   ```

4. Review the hints and make your next guess

## Example Gameplay

```
Enter the color
r - red
b - blue
g - green
y - yellow
v - violet
o - orange

r
b
g
y
O.o.
Try again

r
g
b
y
Oo..
Try again

r
o
b
y
OOo.
Try again

r
o
y
b
OOOO
```

**Note**: `OOOO` means you've won! All colors are correct and in the right positions.

## Code Structure

### Key Components

1. **Code Generation**: Creates a random 4-color code from 6 possible colors
2. **Code Duplication**: Maintains a backup copy to restore after processing
3. **Exact Match Detection**: Checks for colors in correct positions first
4. **Partial Match Detection**: Checks for correct colors in wrong positions
5. **Hint Reset**: Clears hints and code backup for the next guess

### Data Structures

- `vector<char> code(8)`: Stores the secret code and its backup
- `vector<char> guess(4)`: Stores the player's current guess
- `vector<char> hints(4)`: Stores the hints to display
- `vector<bool> hintBool(4)`: Tracks which positions have been matched

## Technical Details

### Algorithm Overview

1. Generate 4 random colors and duplicate them (positions 0-3 and 4-7)
2. Accept player input with validation
3. First pass: Mark exact matches (correct color, correct position)
4. Second pass: Mark partial matches (correct color, wrong position)
5. Display hints and restore the code for next guess
6. Repeat until win or 10 attempts exhausted

### Why Size 8 for Code Vector?

The code vector has size 8 to maintain both:
- The working copy (indices 0-3): Modified during hint generation
- The backup copy (indices 4-7): Used to restore the original code each turn

## Learning Objectives

This project demonstrates:
- C++ STL containers (vectors)
- Random number generation with `srand()` and `rand()`
- Game logic implementation
- Input validation
- Algorithm design for match detection
- State management between turns

## Known Issues & Improvements

### Current Limitations
- The win condition check could be more explicit
- No replay option without restarting the program
- Limited to single-player mode

### Potential Enhancements
- Add difficulty levels (more colors or positions)
- Implement a scoring system
- Add a replay option
- Create a two-player mode
- Display turn history
- Add time-based challenges
- Improve hint visualization (colors, symbols)
- Use better random number generation (`<random>` library)

## Tips for Playing

1. Start with completely different colors to maximize information
2. Pay attention to both 'O' and 'o' hints
3. Use elimination to narrow down possibilities
4. Remember that colors can repeat
5. The order of hints doesn't match the order of your guess

## Troubleshooting

**Problem**: Invalid color entered
- **Solution**: Only enter single-letter color codes: r, b, g, y, v, o

**Problem**: Game seems to accept wrong answers
- **Solution**: Remember 'o' (lowercase) means right color but wrong position

---

*Part of C++ Learning Projects Collection (2016-2017)*
