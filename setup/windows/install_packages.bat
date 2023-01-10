@echo off

IF "%VCPKG%"=="" (
	ECHO Environment variable VCPKG is NOT defined.
	ECHO please install vcpkg and set the variable,
	ECHO for example SET VCPKG=C:\VCPKG
	
	EXIT /B
)

SET Libs=sdl2
SET Platforms=x86-windows x64-windows

(FOR %%l in (%Libs%) DO (
	(FOR %%p in (%Platforms%) DO (
		ECHO Installing %%l:%%p
		CALL "%VCPKG%\vcpkg" install %%l:%%p
	))
))

CALL "%VCPKG%\vcpkg" integrate install

PAUSE
@echo on