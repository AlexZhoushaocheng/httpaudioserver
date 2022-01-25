cmake_minimum_required(VERSION 3.5.1)

project(audioserver)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 5.10.1 REQUIRED COMPONENTS Core Network Multimedia)

add_subdirectory(src/3rdparty)


include_directories(dev/httpserver-dev/include
    src/3rdparty/
    src/3rdparty/src
)

link_directories(dev/httpserver-dev/lib)


set(SRC 
src/server.cpp
src/main.cpp
src/player.cpp
src/handle.cpp
src/upload_handle.cpp
src/3rdparty/easylogging/easylogging++.cc
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Network Qt5::Core Qt5::Multimedia qhttpserver)