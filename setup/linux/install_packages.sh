#!/bin/sh

Libs=sdl2
Platforms=x64-linux

for lib in $Libs; do
	for platform in $Platforms; do
		~/vcpkg/vcpkg install $lib:$platform
	done
done