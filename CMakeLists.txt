cmake_minimum_required (VERSION 3.6)
project(admin-bot)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(globals SHARED globals.cpp)

add_executable(adminbot main.cpp)

add_library(ping SHARED ping.cpp)

add_subdirectory(deps/sleepy-discord)
target_link_libraries(globals sleepy-discord)

target_link_libraries(adminbot globals)
target_link_libraries(adminbot dl)
target_link_libraries(adminbot config)

target_link_libraries(ping globals)

set_target_properties(ping PROPERTIES PREFIX "")
set_target_properties(ping PROPERTIES OUTPUT_NAME "ping")
set_target_properties(ping
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/modules"
)
