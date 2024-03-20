#!/bin/bash

core_num=$(grep -c ^processor /proc/cpuinfo)

binfilename=${PWD##*/}

binpath=../libsoslab/bin

# build
echo ""
echo "------------------------ ${PWD##*/} build start. -------------------------"
echo ""
echo "[ ${PWD##*/} ]"

# make clean
res=$?




if [ $res -eq 0 ]; then
    sudo rm -r build
    mkdir build && cd build
    cmake ..
    make
    sudo cp $binfilename ../../libsoslab/bin
    cd ../
fi

if [ $res -eq 0 ]; then
echo "------------------------ ${PWD##*/} build finished. -------------------------"
echo ""
else
echo "------------------------ ${PWD##*/} build failed. -------------------------"
echo ""
fi

# run
if [ $res -eq 0 ]; then
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"${PWD}/$binpath"
    #gdb --args $binpath/$binfilename $1
    $binpath/$binfilename $1
fi
