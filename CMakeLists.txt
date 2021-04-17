cmake_minimum_required (VERSION 3.6)
project(admin-bot)

add_executable(adminbot main.cpp)

add_subdirectory(deps/sleepy-discord)
target_link_libraries(adminbot sleepy-discord)
target_link_libraries(adminbot dl)
