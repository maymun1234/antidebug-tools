# Professional Security Tool

This project is a C++ based security tool that provides a set of features to protect applications from reverse engineering and tampering. It is designed to be used as a DLL that can be integrated into other applications.

## Features

*   **Anti-Debugging:** Detects if the application is being debugged.
*   **License Control:** Provides a simple license checking mechanism.
*   **File Integrity Check:** Verifies the integrity of files using SHA-256 and CRC32 hashes.
*   **Runtime Protection:** Protects the application from runtime memory patching.
*   **Time-based Restrictions:** Allows for time-based restrictions on the application's usage.

## Building the Project

This project uses CMake to generate the build files. To build the project, follow these steps:

1.  **Create a build directory:**
    ```bash
    mkdir build
    ```

2.  **Navigate to the build directory:**
    ```bash
    cd build
    ```

3.  **Run CMake to generate the build files:**
    ```bash
    cmake ..
    ```

4.  **Build the project:**
    ```bash
    make
    ```

This will build the `SecurityTool` library (e.g., `libSecurityTool.so` on Linux or `SecurityTool.dll` on Windows) and the `TestRunner` executable.

## Usage

### SecurityTool Library

The `SecurityTool` library can be linked against your application to use its security features. The library exports the following functions:

*   `void InitExport(void)`: Initializes the security features.
*   `int GetLicenseStatus(void)`: Returns the current license status.
*   `int GetDebuggerTools(void)`: Returns the debugger status.

### TestRunner Executable

The `TestRunner` executable is a simple command-line application that demonstrates how to use the `SecurityTool` library. It initializes the library and prints the license and debugger status.

## Known Issues

*   The file `kılavuz.txt` could not be deleted due to an issue with the tooling handling Unicode characters in filenames. This file can be safely ignored or deleted manually.
