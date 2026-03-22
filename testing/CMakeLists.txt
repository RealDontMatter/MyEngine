project(testing)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

find_package(GTest REQUIRED)

add_executable(tests
        game_object.cpp
        texture_manager.cpp
        instantiate.cpp
)

target_link_libraries(tests PUBLIC engine)
target_link_libraries(tests PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_link_libraries(tests PUBLIC GTest::gtest GTest::gtest_main)

gtest_discover_tests(tests)

