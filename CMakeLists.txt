cmake_minimum_required(VERSION 3.19)
project(macos-alert)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)

add_executable(macos-alert src/main.cpp src/Alert.h src/Alert.mm src/INI.h)

target_link_libraries(macos-alert "-framework Cocoa")
