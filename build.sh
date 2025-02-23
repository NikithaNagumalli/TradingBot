#!/bin/bash
set -e

if [[ ! -d build ]]
then
    echo "[INFO] Build directory does not exist, creating..."
    mkdir -p build
else
    echo "[INFO] Build directory found"
fi
cmake build
cmake --build .
cd ..
./build/TradingBot
