clang++ -std=c++11 -Wall -c -I./include/ -o main.o ./src/main.cpp 
clang++ -std=c++11 -Wall -c -I./include/ -o snake.o ./src/snake.cpp
clang++ -std=c++11 -Wall -L/usr/local/Cellar/sfml/2.5.1/lib -L./lib/OSX -rpath ./lib/OSX/extlibs -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o snake main.o snake.o
rm ./*.o
mv ./snake ./bin
chmod 755 ./bin/snake
./bin/snake