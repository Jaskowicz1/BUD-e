cmake_minimum_required (VERSION 3.20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(MySQL)

project("BUDe" VERSION 0.5 DESCRIPTION "A friendly discord bot!")

file(GLOB bude_src CONFIGURE_DEPENDS "src/*.h" "src/*.cpp" "src/*/*.h" "src/*/*.cpp" "src/*/*/*.h" "src/*/*/*.cpp")

# Add source to this project's executable.
add_executable(${PROJECT_NAME}
	${bude_src}
		src/commands/info_command.cpp # Much love to GLOB <3
)

if(EXISTS "/usr/include/fmt/format.h")
	target_precompile_headers(${PROJECT_NAME} INTERFACE "/usr/include/fmt/format.h")
	MESSAGE(STATUS "Found FMT.")
else ()
	message(FATAL_ERROR "Could not find FMT. Please install libfmt-dev.")
endif ()

string(ASCII 27 Esc)

# ===============================================
# Required stuff for coro:

target_compile_definitions(${PROJECT_NAME} PUBLIC
	DPP_CORO
)

target_compile_features(${PROJECT_NAME} PUBLIC
	cxx_std_20
)

set(DPP_CORO on)

# Coro stuff over.
# ===============================================

add_subdirectory(libs/DPP)

target_link_libraries(${PROJECT_NAME}
	fmt
	mysqlclient
	dpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	libs/DPP/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CMAKE_STANDARD 20
	CMAKE_STANDARD_REQUIRED ON
)
