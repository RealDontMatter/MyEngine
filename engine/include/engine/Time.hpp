#pragma once
#include <chrono>

namespace engine {
    class Time {
    private:
        static std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        static float deltaTime;
    public:
        static void Init();
        static void Update();
        static float GetDeltaTime();


    };
}
