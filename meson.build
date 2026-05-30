project('Crunch Engine 3', 'cpp', 'c',
    version: '3.0.1',
    default_options: [
        'cpp_std=c++17',
        'c_std=c11'
    ])

# Include folders
include_dir = include_directories('include')
glad_dir = include_directories('deps/glad/include/')
deps_dir= include_directories('deps/')

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
        'src/core/renderer/Shapes.cpp',
        'src/core/Camera.cpp',
        'src/core/FirstPersonController.cpp',
        'src/core/FlyCamera.cpp',
        'src/core/Texture.cpp',
        'src/core/renderer/MeshRegistry.cpp',

        'src/core/renderer/Matrix/Matrix.cpp',

        'src/physics/RigidBody.cpp',
        'src/physics/Physics.cpp',
        'src/physics/Collision.cpp',

        'deps/glad/src/glad.c',
    ],
    dependencies: [glfw_dep, glm_dep],
    include_directories: [include_dir, glad_dir, deps_dir]
)

# Test Executable
executable('CrunchTest', 
    sources: 'CrunchTest.cpp',
    link_with: crunch,
    include_directories: [include_dir, glad_dir],
    dependencies: [glfw_dep, glm_dep]
)
