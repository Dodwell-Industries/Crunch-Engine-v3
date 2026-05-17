project('Crunch Engine 3', 'cpp', 'c')

# Include folders
include_dir = include_directories('include')
glad_dir = include_directories('deps/glad/include/')

# Dependencies
glfw_dep = dependency('glfw3', required: true)
glm_dep = dependency('glm', required: true)

crunch = both_libraries('crunch',
    sources: [
        'src/main.cpp',
        'src/core/Window.cpp',
        'src/core/renderer/Renderer3D.cpp',
        'src/core/renderer/Mesh.cpp',
        'src/core/renderer/Shader.cpp',
        'src/core/Camera.cpp',

        'deps/glad/src/glad.c',
    ],
    dependencies: [glfw_dep, glm_dep],
    include_directories: [include_dir, glad_dir]
)

# Test Executable
executable('CrunchTest', 
    sources: 'CrunchTest.cpp',
    link_with: crunch,
    include_directories: [include_dir, glad_dir],
    dependencies: [glfw_dep, glm_dep]
)
