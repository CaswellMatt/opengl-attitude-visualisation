file(GLOB GL_RENDERER_SRC
    "*.h"
    "*.cpp"
)

add_library (gl-renderer ${GL_RENDERER_SRC})
target_link_libraries(gl-renderer OpenGL::OpenGL)
