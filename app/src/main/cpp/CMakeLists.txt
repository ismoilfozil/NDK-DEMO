
cmake_minimum_required(VERSION 3.10.2)

add_library(main-activity SHARED main-native.cpp)
add_library(second-activity SHARED main-native.cpp)

find_library(log-lib log)

target_link_libraries(main-activity ${log-lib})
target_link_libraries(second-activity ${log-lib})