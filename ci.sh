#!/bin/bash

echo "Running CMake"
if [ -z "$COMPILER" ]; then
	cmake .
else
	echo Overriding C++ compiler to $COMPILER
	cmake -DCMAKE_CXX_COMPILER=$COMPILER .
fi

echo "Compiling"
make

echo "Testing"
cd test
ctest

cd ..
doxygen doxygen.conf
