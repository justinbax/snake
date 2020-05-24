@echo off

REM B-L-0-C-K-S - Proof of Concept block game inspired by Tetris
REM Copyright (C) 2020  Justin BAX and Chris YANG
REM
REM    This program is free software: you can redistribute it and/or modify
REM    it under the terms of the GNU General Public License as published by
REM    the Free Software Foundation, either version 3 of the License, or
REM    any later version.
REM
REM    This program is distributed in the hope that it will be useful,
REM    but WITHOUT ANY WARRANTY; without even the implied warranty of
REM    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
REM    GNU General Public License for more details.
REM
REM    You should have received a copy of the GNU General Public License
REM    along with this program.  If not, see <https://www.gnu.org/licenses/>.

echo Make sure to run this file from the downloaded repository folder and have installed MinGW64 7.3.0 (x64) [The exact version is IMPORTANT]
echo You can download it from the SFML website or the sourceforge link in the README
echo MinGW binaries must be added to your PATH, if it's not there, the compile will fail
echo.

set /p installDIR="Enter Install Path [..\bin\] : "

IF NOT DEFINED installDIR (SET installDIR=..\bin)
mkdir %installDIR%
echo Installing to %installDIR%

echo Compiling, please wait...
g++ -Wall -c -I..\include\ -o main.o ..\src\main.cpp 
g++ -Wall -c -I..\include\ -o block.o ..\src\block.cpp
g++ -Wall -L..\lib\Windows -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -lsfml-audio-2 -o main.exe main.o block.o
echo Cleaning up...
# del .\*.o
echo Compiling Process Completed, moving Install into installation directory at %installDIR%
copy ..\lib\Windows\*.dll %installDIR%\*.dll
xcopy /E /I ..\content ..\bin\content
move .\main.exe %installDIR%\main.exe
ren %installDIR%\*.exe b-l-o-c-k-s.exe
echo All Done! :D


