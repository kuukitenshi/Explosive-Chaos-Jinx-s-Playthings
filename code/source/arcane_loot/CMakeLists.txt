set(ARCANE_LOOT_SOURCES
    "src/main.cpp"
    "src/nodes/object_node.cpp"
    "src/nodes/normal_object_node.cpp"
    "src/nodes/cristal_ball_node.cpp"
    "src/nodes/skybox_node.cpp"

    "src/scene.cpp"
    "src/procedural_texture.cpp"
)

add_executable(arcane_loot ${ARCANE_LOOT_SOURCES})
target_link_libraries(arcane_loot PRIVATE tangram-engine)
add_dependencies(arcane_loot copy_assets)
