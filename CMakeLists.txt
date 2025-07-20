cmake_minimum_required(VERSION 3.10.0)
project(TFM VERSION 0.1.0 LANGUAGES C CXX)

set(INC ui core)
set(SRC main.cpp ui/renderer.cpp core/context.cpp)

add_executable(TFM ${SRC})

find_package(Curses REQUIRED)
target_link_libraries(TFM PRIVATE ${CURSES_LIBRARIES})

target_include_directories(TFM PRIVATE ${CURSES_INCLUDE_DIR})

