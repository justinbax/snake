## B-L-0-C-K-S - Proof of Concept block game inspired by Tetris
## Copyright (C) 2020  Justin BAX and Chris YANG
##
##    This program is free software: you can redistribute it and/or modify
##    it under the terms of the GNU General Public License as published by
##    the Free Software Foundation, either version 3 of the License, or
##    any later version.
##
##    This program is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU General Public License for more details.
##
##    You should have received a copy of the GNU General Public License
##    along with this program.  If not, see <https://www.gnu.org/licenses/>.

echo "Make sure to run the script in the downloaded repo directory and as a standard user"
echo "Clang/LLVM is required to compile this program, please make sure it's installed"
echo "Be aware that this script might ask for your password to run sudo commands while cleaning up."


read -p 'Binary Install Directory [./bin]: ' INSTALLDIR
if [[ -z $INSTALLDIR ]]; then
    INSTALLDIR="./bin"
fi
mkdir $INSTALLDIR
echo "Compiling, please wait..."
clang++ -std=c++11 -Wall -c -I./include/ -o main.o ./src/main.cpp 
clang++ -std=c++11 -Wall -c -I./include/ -o block.o ./src/block.cpp
clang++ -std=c++11 -Wall -L/usr/local/Cellar/sfml/2.5.1/lib -L./lib/OSX -rpath ./lib/OSX/extlibs -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o b-l-o-c-k-s main.o block.o
echo "Cleaning up..."
rm ./*.o
echo "Compilation Process Completed, moving binaries to $INSTALLDIR"
mv ./b-l-o-c-k-s $INSTALLDIR
echo "Updating permissions"
chown root:admin $INSTALLDIR/b-l-o-c-k-s
chmod 755 $INSTALLDIR/b-l-o-c-k-s
echo "All Done :D"
echo "To run the program, simply run ./bin/b-l-o-c-k-s"

