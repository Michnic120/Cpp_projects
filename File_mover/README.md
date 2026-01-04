# File Mover

A Windows-based file management utility written in C++ that provides robust file moving operations with comprehensive error handling.

## Description

This program allows users to move files from one location to another on Windows systems. It utilizes the Windows API for file operations and includes error detection and reporting capabilities. The application continues to prompt for file operations until successful completion.

## Features

- **File Moving**: Move files from source to destination paths
- **Error Handling**: Comprehensive exception handling with specific error codes
- **User-Friendly Interface**: Clear prompts and error messages
- **Retry Logic**: Automatically prompts for retry on failure
- **Windows API Integration**: Uses native Windows file system operations

## Technical Details

### Technologies Used
- C++ Standard Library
- Windows API (`windows.h`)
- Console I/O (`conio.h`)

### Key Functions
- `Move()`: Handles the file moving operation with try-catch error handling
- `ErrorList(int error)`: Maps Windows error codes to user-friendly messages
- Uses `MoveFileA()` from Windows API for actual file operations
- `GetLastError()` for detailed error reporting

## Prerequisites

- Windows Operating System
- C++ compiler with Windows API support (MSVC recommended)
- Windows SDK

## How to Build

### Using MSVC (Visual Studio)

```bash
cl /EHsc file_mover.cpp /link user32.lib
```

### Using MinGW

```bash
g++ file_mover.cpp -o file_mover.exe
```

## How to Run

1. Execute the compiled program:
   ```bash
   file_mover.exe
   ```

2. When prompted, enter the full source path of the file you want to move:
   ```
   Enter source of the file: C:\path\to\source\file.txt
   ```

3. Enter the destination path:
   ```
   Enter destination path: C:\path\to\destination\file.txt
   ```

4. The program will attempt to move the file and display success or error messages

5. If an error occurs, the program will prompt you to try again

## Error Codes

| Code | Description |
|------|-------------|
| 0    | Success - file moved successfully |
| 2    | File not found - check the source path |

## Example Usage

```
Enter source of the file: C:\Users\Documents\test.txt
Enter destination path: D:\Backup\test.txt
C:\Users\Documents\test.txt file moved successfully.
```

## Limitations

- Windows-only (uses Windows API)
- Requires full file paths (not directory paths)
- Cannot move directories, only individual files
- Overwrites existing files at destination without confirmation

## Learning Objectives

This project demonstrates:
- Working with Windows API
- File system operations
- Exception handling in C++
- Error code interpretation
- User input validation and processing

## Future Improvements

Potential enhancements could include:
- Cross-platform support using standard C++17 filesystem library
- Directory moving capability
- Overwrite confirmation prompt
- GUI interface
- Batch file operations
- Progress indication for large files

---

*Part of C++ Learning Projects Collection (2016-2017)*
