@echo off
setlocal EnableExtensions EnableDelayedExpansion

where g++ >nul 2>nul
if errorlevel 1 (
    echo Error: g++ was not found. Install MSYS2 or MinGW-w64 and add it to PATH.
    exit /b 1
)

if not exist build mkdir build

set "SOURCES="
for %%F in (src\*.cpp) do set "SOURCES=!SOURCES! %%F"

g++ -std=c++17 -Iinclude !SOURCES! -o build\CountMyCash.exe
if errorlevel 1 exit /b 1

echo Build complete: build\CountMyCash.exe
