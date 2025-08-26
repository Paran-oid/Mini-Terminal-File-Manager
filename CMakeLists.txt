# CONFIG

cmake_minimum_required(VERSION 3.10.0)
project(TFM VERSION 0.1.0 LANGUAGES C CXX)

# FLAGS

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# enable signals to be intercepted while debugging
add_compile_options(-g -O0)   # Debug info, no optimizations
add_link_options(-g -O0)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Enable debugging symbols
set(CMAKE_BUILD_TYPE Debug)

# Doxygen-related

# Find Doxygen
find_package(Doxygen REQUIRED)

# Set Doxygen config
set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

if (DOXYGEN_FOUND)
    # Copy Doxyfile and substitute variables if needed
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Add a custom target
	add_custom_target(docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
	)
endif()


# SRC and include directories

set(SRC 
	utils/utils.cpp
	src/file.cpp
	src/main.cpp
	src/renderer.cpp
	src/input.cpp
	src/screen.cpp
	src/rows.cpp
	src/cursor.cpp
	src/path.cpp
	src/dialog.cpp
	src/commands/command_history.cpp
	src/commands/command_handler.cpp
	src/commands/command_executor.cpp
	src/commands/command_mapper.cpp
	src/commands/command_parser.cpp
)

set(include_dir
	${CMAKE_SOURCE_DIR}/utils
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/commands)

# executables and including files and packages

add_executable(TFM ${SRC})

# Compiler warnings and errors - GCC/Clang
target_compile_options(TFM PRIVATE
    -Wall            # Enable most warnings
    -Wextra          # Enable extra warnings
    -Wpedantic       # Enforce strict ISO compliance
    -Werror          # Treat warnings as errors
    -Wshadow         # Warn on variable shadowing
    -Wconversion     # Warn on implicit conversions
    -Wsign-conversion # Warn on signed/unsigned conversions
    -Wformat=2       # Enable extra format checking
    -fsanitize=address # Optional: Address sanitizer for runtime memory errors (if supported)
)

# For MSVC compiler, a similar set:
if(MSVC)
    target_compile_options(TFM PRIVATE
        /W4       # Warning level 4 (highest)
        /WX       # Treat warnings as errors
        /permissive-  # Strict standard compliance
        /Zc:__cplusplus  # Enable latest C++ conformance mode
    )
endif()

find_package(Curses REQUIRED)
target_link_libraries(TFM PRIVATE ${CURSES_LIBRARIES})

target_include_directories(TFM PRIVATE 
	${CURSES_INCLUDE_DIR} ${include_dir}        
)

