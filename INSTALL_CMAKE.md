# 🔧 How to Install CMake

CMake is a cross-platform build system that makes compiling C++ projects easier. Here's how to install it on different operating systems.

---

## macOS (Your System)

### Method 1: Using Homebrew (Recommended)

**Step 1:** Check if Homebrew is installed
```bash
brew --version
```

If you see a version number, Homebrew is installed. Skip to Step 3.

**Step 2:** Install Homebrew (if not installed)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

After installation, follow the on-screen instructions to add Homebrew to your PATH.

**Step 3:** Install CMake
```bash
brew install cmake
```

**Step 4:** Verify installation
```bash
cmake --version
```

You should see something like:
```
cmake version 3.28.0
```

---

### Method 2: Download from Official Website

1. Visit: https://cmake.org/download/
2. Download the macOS `.dmg` file
3. Open the `.dmg` file
4. Drag CMake to Applications folder
5. Add CMake to PATH:
   ```bash
   # Add this to your ~/.zshrc file
   export PATH="/Applications/CMake.app/Contents/bin:$PATH"
   ```
6. Reload your shell:
   ```bash
   source ~/.zshrc
   ```

---

## Windows

### Method 1: Using Chocolatey (Recommended)

**Step 1:** Install Chocolatey (if not installed)
- Open PowerShell as Administrator
- Run:
  ```powershell
  Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
  ```

**Step 2:** Install CMake
```powershell
choco install cmake
```

**Step 3:** Verify
```powershell
cmake --version
```

---

### Method 2: Official Installer

1. Visit: https://cmake.org/download/
2. Download the Windows `.msi` installer
3. Run the installer
4. **Important:** During installation, select "Add CMake to system PATH for all users"
5. Complete installation
6. Open new Command Prompt and verify:
   ```cmd
   cmake --version
   ```

---

## Linux

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install cmake
cmake --version
```

### Fedora/RHEL
```bash
sudo dnf install cmake
cmake --version
```

### Arch Linux
```bash
sudo pacman -S cmake
cmake --version
```

---

## 🚀 Using CMake with This Project

Once CMake is installed, build the project:

```bash
# Navigate to project directory
cd "/Users/adityakulkarni/Downloads/Projects/DSA-Project_CustomCPP lib"

# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run the programs
./DSA_Library
./DSA_Examples
./DSA_Tests
```

---

## 📝 What CMake Does

Instead of manually typing:
```bash
clang++ -std=c++17 -Wall -Wextra -I./include src/main.cpp -o DSA_Library
clang++ -std=c++17 -Wall -Wextra -I./include examples/usage_examples.cpp -o DSA_Examples
clang++ -std=c++17 -Wall -Wextra -I./include tests/test_data_structures.cpp -o DSA_Tests
```

You just type:
```bash
cmake --build .
```

CMake automatically:
- Detects your compiler (clang++, g++, MSVC)
- Sets correct flags
- Handles dependencies
- Works on Mac, Windows, Linux

---

## 🔍 Troubleshooting

### "cmake: command not found"

**Solution:** CMake is not in your PATH.

**macOS:**
```bash
# Add to ~/.zshrc
export PATH="/usr/local/bin:$PATH"
source ~/.zshrc
```

**Windows:**
- Search for "Environment Variables" in Start Menu
- Edit "Path" variable
- Add CMake installation directory (usually `C:\Program Files\CMake\bin`)

---

### "Could not find a package configuration file provided by..."

**Solution:** Install missing dependencies.

For this project, you only need a C++ compiler (clang++, g++, or MSVC).

---

### CMake version too old

**Solution:** Update CMake.

**macOS:**
```bash
brew upgrade cmake
```

**Linux:**
```bash
sudo apt upgrade cmake  # Ubuntu/Debian
sudo dnf upgrade cmake  # Fedora
```

---

## 🎯 Do You Actually Need CMake?

**Short answer: Not for this project!**

This project is simple enough to build with the provided `build.sh` script:
```bash
./build.sh
```

**When you DO need CMake:**
- Large projects with many files
- Cross-platform projects
- Projects with external dependencies
- Professional/industry projects

**For this learning project:**
- Use `build.sh` for simplicity
- Learn CMake for future professional projects

---

## 📚 Learning CMake (Optional)

If you want to understand CMake better:

**Basic CMakeLists.txt structure:**
```cmake
# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(MyProgram main.cpp)
```

**Useful resources:**
- Official tutorial: https://cmake.org/cmake/help/latest/guide/tutorial/
- CMake by Example: https://github.com/ttroy50/cmake-examples

---

## ✅ Quick Install Summary

**macOS (easiest):**
```bash
brew install cmake
```

**Windows (easiest):**
```powershell
choco install cmake
```

**Linux (easiest):**
```bash
sudo apt install cmake  # Ubuntu/Debian
```

**Verify:**
```bash
cmake --version
```

**Build this project:**
```bash
cd "/Users/adityakulkarni/Downloads/Projects/DSA-Project_CustomCPP lib"
mkdir build && cd build
cmake ..
cmake --build .
```

**Or just use the build script (no CMake needed):**
```bash
./build.sh
```

---

That's it! CMake is now installed and you can build C++ projects professionally. 🎉
