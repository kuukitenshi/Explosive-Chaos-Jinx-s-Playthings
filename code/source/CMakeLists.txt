cmake_minimum_required(VERSION 3.26)

project(cgj-tangram VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../release)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
        "${CMAKE_SOURCE_DIR}/assets/"
        "$<TARGET_FILE_DIR:arcane_loot>/assets"
)


# Add subdirs
add_subdirectory("engine")
add_subdirectory("arcane_loot")
