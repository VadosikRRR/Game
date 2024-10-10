add_library(RogueLike map/map.cpp map/room.cpp basic_classes/item.cpp basic_classes/point.cpp Hero/Hero.cpp Game.cpp 
    )

target_link_libraries(${PROJECT_NAME} ncurses)
target_include_directories(RogueLike PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})