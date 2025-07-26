cmake_minimum_required(VERSION 3.10.0)
project(TFM VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(INC ui/render ui/input core/builtins core)
set(SRC 
	main.cpp
 	core/context.cpp 
	core/builtins/builtins.cpp
	ui/input/input.cpp 
	ui/render/render.cpp
	utils/string_utils.cpp
	utils/misc.cpp
	core/parser/parser.cpp
)

add_executable(TFM ${SRC})

find_package(Curses REQUIRED)
target_link_libraries(TFM PRIVATE ${CURSES_LIBRARIES})

target_include_directories(TFM PRIVATE 
	${CURSES_INCLUDE_DIR}        
	${CMAKE_SOURCE_DIR}/utils
	${CMAKE_SOURCE_DIR}/ui/input
	${CMAKE_SOURCE_DIR}/ui/render
	${CMAKE_SOURCE_DIR}/core
	${CMAKE_SOURCE_DIR}/core/builtins
	${CMAKE_SOURCE_DIR}/core/parser
)

