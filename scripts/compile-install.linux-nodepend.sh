#!/bin/bash

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
echo "Skipping system dependency pull"
echo "The required libraries are in ./lib/Linux, to run the program, specify the directory in the LD_LIBRARY_PATH variable"
echo "i.e.  $ LD_LIBRARY_PATH=./lib/linux ./b-l-o-c-k-s"
echo "Clang is required to compile this program, please make sure it's installed"
echo 

##
# if [[ $(cat /etc/*-release | grep "ID_LIKE") = *debian* ]]; then
#   sudo apt-get update && sudo apt-get install -y libsfml-dev clang
# elif [[ $(cat /etc/*-release | grep "ID") = *arch* ]]; then
#    sudo pacman -Syy sfml clang sudo --needed --noconfirm
# elif [[ $(cat /etc/*-release | grep "ID") = *fedora* ]]; then
#    sudo dnf check-update && sudo dnf install -y compat-SFML16 clang
# else
#    echo "Unable to automatically resolve dependencies due to incompatible distribution"
#    echo "Please make sure to resolve dependencies manually if not already done"
#    echo "SFML Libraries are in the ./lib/Linux folder"
#    echo "The build will continue"
# fi
##

read -p 'Binary Install Directory [../bin]: ' INSTALLDIR
if [[ -z $INSTALLDIR ]]; then
    INSTALLDIR="../bin"
fi
mkdir $INSTALLDIR
echo "Compiling, please wait..."
clang++ -Wall -c -I../include/ -o main.o ../src/main.cpp 
clang++ -Wall -c -I../include -o block.o ../src/block.cpp
clang++ -Wall -L../lib/Linux -L/lib -L/usr/lib -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -o main main.o
echo "Cleaning up..."
sudo rm ./*.o
echo "Compilation Process Completed, moving binaries to $INSTALLDIR"
sudo mv ./main $INSTALLDIR/b-l-o-c-k-s
echo "Updating permissions"
sudo chown root:root $INSTALLDIR/b-l-o-c-k-s
sudo chmod 755 $INSTALLDIR/b-l-o-c-k-s
echo "All Done :D"
