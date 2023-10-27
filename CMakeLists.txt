cmake_minimum_required (VERSION 3.20)

project ("BUDe"	VERSION 0.5 DESCRIPTION "A friendly discord bot!")

file(GLOB bude_src CONFIGURE_DEPENDS "src/*.h" "src/*.cpp" "src/*/*.h" "src/*/*.cpp")

# Add source to this project's executable.
add_executable(${PROJECT_NAME}
	${bude_src} # Much love to GLOB <3
)

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
	dpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	libs/DPP/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CMAKE_STANDARD 20
	CMAKE_STANDARD_REQUIRED ON
)
