cmake_minimum_required(VERSION 3.10)


project(RogueLike)

add_subdirectory(src)

add_executable(app src/main.cpp)

target_link_libraries(app RogueLike)
