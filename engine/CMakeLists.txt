add_library(engine STATIC
    src/core/Entity.cpp
    src/core/Scene.cpp
    src/core/System.cpp
    src/graphics/Renderer.cpp
    src/graphics/Sprite.cpp
    src/graphics/BackgroundManager.cpp
    src/physics/Transform.cpp
    src/physics/Velocity.cpp
    src/systems/RenderSystem.cpp
    src/systems/MovementSystem.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
)