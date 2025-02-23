#!/bin/bash
set -e
set -x

mkdir build
cd build
cmake ..
cmake --build .
cd ..
./build/TradingBot