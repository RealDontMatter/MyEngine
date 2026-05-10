project(engine)
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
        src/Component.cpp
        src/GameObject.cpp
        src/Vector3.cpp
        src/TextureManager.cpp
        src/Time.cpp
        src/Level.cpp
        src/RenderPipeline.cpp
        src/components/Camera.cpp
        src/components/Sprite.cpp
        src/components/Transform.cpp
        src/components/PerspectiveCamera.cpp
        src/LevelManager.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system sfml-graphics sfml-window sfml-network sfml-audio
)
