cmake_minimum_required(VERSION 3.5.1)

project(audioserver)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


find_package(Qt5 5.10.1 REQUIRED COMPONENTS Core Network Multimedia)

include_directories(dev/httpserver-dev/include)

link_directories(dev/httpserver-dev/lib)


set(SRC 
src/server.cpp
src/main.cpp
src/player.cpp
src/handle.cpp
src/upload_handle.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Network Qt5::Core Qt5::Multimedia qhttpserver)