cmake_minimum_required(VERSION 3.14)
project(02_Array)

set(CMAKE_CXX_STANDARD 17)

add_executable(dyn_array DynArrayMain.cpp)
add_executable(priority_queue PriorityQueueMain.cpp)
target_link_libraries(dyn_array -static)
target_link_libraries(priority_queue -static)