project(demo)
set(CMAKE_CXX_STANDARD 20)


add_executable(${PROJECT_NAME} src/main.cpp src/PlayerMovement.cpp src/EnemyLogic.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE
        engine
        sfml-system sfml-graphics sfml-window sfml-network sfml-audio
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_INSTALL_PREFIX})
