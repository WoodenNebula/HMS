@echo off
setlocal enabledelayedexpansion

cd /d "%~dp0"
mingw32-make.exe clean
.\premake\premake5.exe gmake
mingw32-make.exe
pause
if exist ".\bin\HotelManagementService.out.exe" (
    .\bin\HotelManagementService.out.exe
) else (
    echo ERROR: Executable not found!
)
pause
