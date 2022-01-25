


find_package(Qt5 5.10.1 REQUIRED COMPONENTS Core Network Multimedia)

file(GLOB HTTP_SRC src/*.cpp)
# message(STATUS ${HTTP_SRC})
include_directories(./http-parser)

add_library(qhttpserver ${HTTP_SRC}
http-parser/http_parser.c
)

target_link_libraries(qhttpserver Qt5::Network Qt5::Core)