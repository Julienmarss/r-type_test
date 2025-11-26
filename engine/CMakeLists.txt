add_library(engine STATIC
    src/core/Entity.cpp
    src/core/Scene.cpp
    src/core/System.cpp
    src/graphics/Renderer.cpp
    src/graphics/Sprite.cpp
    src/graphics/Animation.cpp
    src/physics/Transform.cpp
    src/physics/Velocity.cpp
    src/gameplay/Controllable.cpp
    src/gameplay/Projectile.cpp 
    src/systems/RenderSystem.cpp
    src/systems/MovementSystem.cpp
    src/systems/ScrollingBackgroundSystem.cpp
    src/systems/InputSystem.cpp
    src/systems/BoundarySystem.cpp
    src/systems/AnimationSystem.cpp
    src/systems/ShootingSystem.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
)