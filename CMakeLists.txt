cmake_minimum_required(VERSION 3.10)
project(Battle_of_Kinmen)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_PREFIX_PATH
    "D:/SDL3-3.2.24/cmake"
    "D:/SDL3_ttf-3.2.2/cmake"
)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(Battle_of_Kinmen main.cpp
    buttons.h
    data.h
    text_texture.h
    scene.h
    text_texture.cpp)

target_link_libraries(Battle_of_Kinmen PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)