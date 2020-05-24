#!/bin/bash

echo -n "Compiling ... "
clang++ -std=c++11 -Wall -c -I./include -I./frameworks -D __BUILD_APPLICATION_OSX__ -o main.o ./src/main.cpp
clang++ -std=c++11 -Wall -L./lib/OSX -rpath ./lib/OSX/extlibs -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -F./frameworks -framework CoreFoundation -o main main.o
echo -n "done"
echo
echo -n "Cleaning up ... "
rm *.o
echo -n "done"
echo
echo -n "Creating application ... "
mkdir -p main.app/Contents/MacOS
mv main main.app/Contents/MacOS
echo -n "done"
echo
echo -n "Copying libraries ... "
cp ./lib/OSX/*.dylib ./main.app/Contents/MacOS
echo -n "& content files ... "
cd ./main.app/Contents
mkdir Resources
cd ../
cd ../
# cp rel_path_to_resources ./main.app/Contents/Resources
echo -n "& Info.plist ... "
# cp rel_path_to_Info.plist ./main.app/Contents
echo -n "done"
echo
echo -n "Changing dependencies location ... "
install_name_tool -change ./lib/OSX/libsfml-graphics.2.5.1.dylib @executable_path/libsfml-graphics.2.5.1.dylib main.app/Contents/MacOS/main
install_name_tool -change ./lib/OSX/libsfml-window.2.5.1.dylib @executable_path/libsfml-window.2.5.1.dylib main.app/Contents/MacOS/main
install_name_tool -change ./lib/OSX/libsfml-system.2.5.1.dylib @executable_path/libsfml-system.2.5.1.dylib main.app/Contents/MacOS/main
install_name_tool -change ./lib/OSX/libsfml-audio.2.5.1.dylib @executable_path/libsfml-audio.2.5.1.dylib main.app/Contents/MacOS/main

install_name_tool -change /usr/local/opt/sfml/lib/libsfml-graphics.2.5.dylib @executable_path/libsfml-graphics.2.5.1.dylib main.app/Contents/MacOS/main
install_name_tool -change /usr/local/opt/sfml/lib/libsfml-window.2.5.dylib @executable_path/libsfml-window.2.5.1.dylib main.app/Contents/MacOS/main
install_name_tool -change /usr/local/opt/sfml/lib/libsfml-system.2.5.dylib @executable_path/libsfml-system.2.5.1.dylib main.app/Contents/MacOS/main
install_name_tool -change /usr/local/opt/sfml/lib/libsfml-audio.2.5.dylib @executable_path/libsfml-audio.2.5.1.dylib main.app/Contents/MacOS/main
echo -n "done"
echo