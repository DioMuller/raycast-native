@echo off

:: Check if Admin
net session >nul 2>&1
IF %errorLevel% NEQ 0 (
	echo User needs admin permissions to run this script.
	exit /b 0
)

:: Set path
IF "%1"=="" (
	ECHO Downloading VCPKG to default directory
	SET "vckpgpath=C:\vcpkg"
) ELSE (
	SET "vckpgpath=%1"
)

:: Install VCPKG
SETX VCPKG "%vckpgpath%"

git clone https://github.com/Microsoft/vcpkg %vckpgpath%
CALL %vckpgpath%\bootstrap-vcpkg.bat
@echo on