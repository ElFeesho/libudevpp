#!/bin/bash

echo "Running CMake"
cmake .

echo "Compiling"
make

echo "Testing"
cd test
./monitor_test
