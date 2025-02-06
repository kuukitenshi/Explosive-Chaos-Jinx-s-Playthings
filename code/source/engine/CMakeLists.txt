set(ENGINE_SOURCES
    "src/window/window.cpp"
    "src/window/glfw_window.cpp"

    "src/rendering/camera.cpp"
    "src/rendering/orbit_camera.cpp"
    "src/rendering/color.cpp"
    "src/rendering/vertex_layout.cpp"
    "src/rendering/shader.cpp"
    "src/rendering/model.cpp"
    "src/rendering/graphics_api.cpp"
    "src/rendering/image.cpp"
    "src/rendering/texture.cpp"
    "src/rendering/texture_description.cpp"
    "src/rendering/noise.cpp"
    "src/rendering/procedural_textures.cpp"

    "src/rendering/opengl/vertex_buffer.cpp"
    "src/rendering/opengl/vertex_array.cpp"
    "src/rendering/opengl/uniform_buffer.cpp"
    "src/rendering/opengl/shader.cpp"
    "src/rendering/opengl/shader_program.cpp"
    "src/rendering/opengl/index_buffer.cpp"
    "src/rendering/opengl/graphics_api.cpp"
    "src/rendering/opengl/texture.cpp"

    "src/scene/scene.cpp"
    "src/scene/scene_node.cpp"
    "src/scene/transform.cpp"
)

set(ENGINE_NAME "tangram-engine")

add_library(${ENGINE_NAME} STATIC ${ENGINE_SOURCES})
target_include_directories(${ENGINE_NAME} PUBLIC "include")
target_compile_definitions(${ENGINE_NAME} PRIVATE -DGLFW_INCLUDE_NONE PUBLIC -DGLM_ENABLE_EXPERIMENTAL)

# --------------------------[ IMPORT LIBRARIES ]--------------------------
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

message("Fetching tangram-engine dependencies:")

# >> GLM
message(">> Fetching GLM")
FetchContent_Declare(glm
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_PROGRESS TRUE
    SYSTEM
    FIND_PKG_ARGS
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${ENGINE_NAME} PUBLIC glm)

# >> GLFW
message(">> Fetching GLFW")
FetchContent_Declare(glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_PROGRESS TRUE
    SYSTEM
    FIND_PKG_ARGS
)
FetchContent_MakeAvailable(glfw)
target_link_libraries(${ENGINE_NAME} PRIVATE glfw)

# >> GLAD
message(">> Fetching GLAD")
FetchContent_Declare(glad
	GIT_REPOSITORY "https://github.com/mkuritsu/glad.git"
    GIT_PROGRESS TRUE
	SYSTEM
    FIND_PKG_ARGS
)
FetchContent_MakeAvailable(glad)
target_link_libraries(${ENGINE_NAME} PRIVATE glad)

# >> ASSIMP
message(">> Fetch ASSIMP")
FetchContent_Declare(assimp
    GIT_REPOSITORY "https://github.com/assimp/assimp.git"
    GIT_TAG "5aa38fe3cd9385eb10af16b9cb714eb759b886ef"
    GIT_PROGRESS TRUE
    GIT_SHALLOW FALSE
    SYSTEM
    FIND_PKG_ARGS
)
FetchContent_MakeAvailable(assimp)
target_link_libraries(${ENGINE_NAME} PRIVATE assimp)

# >> STB_IMAGE
message(">> Fetch STB_IMAGE")
FetchContent_Declare(stb_image
    GIT_REPOSITORY "https://github.com/mkuritsu/stb_image.git"
    GIT_PROGRESS TRUE
    GIT_SHALLOW FALSE
    SYSTEM
    FIND_PKG_ARGS
)
FetchContent_MakeAvailable(stb_image)
target_link_libraries(${ENGINE_NAME} PRIVATE stb_image)

# >> STB_IMG_WRITE
message(">> Fetch STB_IMAGE_WRITE")
FetchContent_Declare(stb_image_write
    GIT_REPOSITORY "https://github.com/kuukitenshi/stb_img_write.git"
    GIT_PROGRESS TRUE
    GIT_SHALLOW FALSE
    SYSTEM
    FIND_PKG_ARGS
)
FetchContent_MakeAvailable(stb_image_write)
target_link_libraries(${ENGINE_NAME} PRIVATE stb_image_write)
