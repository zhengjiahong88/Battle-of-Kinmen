cmake_minimum_required(VERSION 3.10)
project(Battle_of_Kinmen)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_PREFIX_PATH
        "D:/SDL3-3.2.24/cmake"
        "D:/SDL3_ttf-3.2.2/cmake"
        "D:/SDL3_image-3.2.4/cmake"
)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

add_executable(Battle_of_Kinmen
        main.cpp
        button.h
        data.h
        texture.h
        texture.cpp
        tcp_socket.h
        tcp_socket.cpp
        basemap.h
        basemap.cpp
        army.h
        state.h
        base.h
        base.cpp
        button.cpp
        commander.cpp
        commander.h
        data.cpp
        army.cpp
)

target_link_libraries(Battle_of_Kinmen PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image ws2_32)