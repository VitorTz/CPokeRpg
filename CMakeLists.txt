cmake_minimum_required(VERSION 3.24...3.30)
project(CPokeRpg)

include(FetchContent)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

# Our Project
add_executable(${PROJECT_NAME})
#file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ./src/*.c)
#file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ./src/*.h)
target_sources(${PROJECT_NAME} PRIVATE "src/main.c" "src/constants.h" "src/util/vector.h" "src/util/iterator.h" "src/util/hash_map.h" "src/util/hash_map.c" "src/util/vector.c" "src/util/util.h" "src/util/util.c" "src/util/texture_pool.h" "src/util/texture_pool.c" "src/scene/scene_id.h" "src/scene/scene.h" "src/scene/scene_manager.c" "src/scene/scene_title_screen.h" "src/scene/scene_title_screen.c" "src/util/image.h" "src/util/image.c" "src/scene/scene_world.h" "src/scene/scene_fire_arena.h" "src/scene/scene_water_arena.h" "src/scene/scene_plant_arena.h" "src/scene/scene_hospital.h" "src/scene/scene_house.h" "src/scene/scene_test.h" "src/scene/scene_world.c" "src/scene/scene_fire_arena.c" "src/scene/scene_water_arena.c" "src/scene/scene_plant_arena.c" "src/scene/scene_hospital.c" "src/scene/scene_house.c" "src/scene/scene_test.c" "src/util/mstring.h" "src/util/mstring.c" "src/ecs/components.h" "src/util/types.h" "src/ecs/component_manager.h" "src/ecs/component_array.h" "src/ecs/component_array.c" "src/ecs/components.c" "src/ecs/component_manager.c" "src/ecs/entity_manager.h" "src/ecs/entity_manager.c" "src/ecs/system_manager.h" "src/util/vector_entity.h" "src/util/vector_entity.c")

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/../resources
    )
    #DEPENDS ${PROJECT_NAME}
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    )
    #DEPENDS ${PROJECT_NAME}
endif()

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file resources)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
