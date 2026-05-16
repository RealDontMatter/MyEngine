project(demo)
set(CMAKE_CXX_STANDARD 20)


add_executable(${PROJECT_NAME}
  src/main.cpp src/PlayerMovement.cpp src/EnemyLogic.cpp src/EnemySpawner.cpp
)

set_target_properties(demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
)
add_custom_command(TARGET demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE
        engine
        sfml-system sfml-graphics sfml-window sfml-network sfml-audio
)

install(TARGETS ${PROJECT_NAME} DESTINATION ./demo/bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION ./demo)
