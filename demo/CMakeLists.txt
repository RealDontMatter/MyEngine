project(demo)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp PlayerMovement.cpp EnemyLogic.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        engine
        sfml-system sfml-graphics sfml-window sfml-network sfml-audio
)
