cmake_minimum_required(VERSION 3.10)

project(TradingBot)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(TradingBot main.cpp Calculations.cpp)

# Include directories
# include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(C:/msys64/mingw64/include)
include_directories(C:/Users/nikit/PersonalProjects/TradingBot/libs)

# Link additional libraries if necessary
target_link_libraries(TradingBot ws2_32)