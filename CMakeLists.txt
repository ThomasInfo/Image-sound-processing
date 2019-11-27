cmake_minimum_required(VERSION 3.15)
project(Image_sound_processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(Image_sound_processing main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Image_sound_processing Threads::Threads)

target_link_libraries(Image_sound_processing X11)
