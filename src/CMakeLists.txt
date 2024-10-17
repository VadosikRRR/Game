file(GLOB_RECURSE SOURCES
    "**/*.cpp"
    "*.cpp"
)

add_library(RogueLike ${SOURCES} )

target_link_libraries(${PROJECT_NAME} ncurses)
target_include_directories(RogueLike PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})