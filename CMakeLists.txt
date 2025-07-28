# CONFIG

cmake_minimum_required(VERSION 3.10.0)
project(TFM VERSION 0.1.0 LANGUAGES C CXX)

# FLAGS

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# SRC and include directories

set(SRC 
	src/main.cpp
	src/config.cpp
	src/terminal.cpp	
)
set(include_dir
	${CMAKE_SOURCE_DIR}/include)

# executables and including files and packages

add_executable(TFM ${SRC})

find_package(Curses REQUIRED)
target_link_libraries(TFM PRIVATE ${CURSES_LIBRARIES})

target_include_directories(TFM PRIVATE 
	${CURSES_INCLUDE_DIR} ${include_dir}        
)

