@echo off

g++ -Wall -c -I./include/ -o main.o ./src/main.cpp 
g++ -Wall -c -I./include/ -o snake.o ./src/snake.cpp
g++ -Wall -L./lib/Windows -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -lsfml-audio-2 -o snake main.o snake.o
.\snake.exe