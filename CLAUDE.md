# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is "Interactive NPU Virtual Library" (互动NPU虚拟图书馆) - a Qt6-based desktop application built with C++. The project is in early development stages.

## Build System

This project uses CMake (minimum version 3.16) with Qt6.

### Building the Project

From the project root:

```bash
# Configure CMake (in build directory)
cmake -B build

# Build the executable
cmake --build build

# The output binary will be placed at: build/bin/LibraryMap.exe
```

Alternatively, use the provided PowerShell script:
```powershell
.\script\build.ps1
```

### Running the Application

```bash
.\build\bin\LibraryMap.exe
```

## Architecture

- **Build System**: CMake with Qt6 automoc enabled
- **Framework**: Qt6 Widgets
- **Entry Point**: `main.cpp` - Creates the QApplication and starts the event loop
- **Project Name**: LibraryMap (as defined in CMakeLists.txt)

## Project Structure

- `CMakeLists.txt` - CMake build configuration
- `main.cpp` - Application entry point
- `build/` - Build output directory (gitignored)
- `script/` - Build scripts
- `.vscode/` - VSCode settings (gitignored)

## Qt Configuration

The project has Qt's meta-object compiler (MOC) auto-enabled via `CMAKE_AUTOMOC`. When adding new Qt classes with Q_OBJECT macro, CMake will automatically handle MOC processing.
