#include <engine/Time.hpp>

std::chrono::time_point<std::chrono::high_resolution_clock> engine::Time::startTime;
float engine::Time::deltaTime;

void engine::Time::Init() {
    startTime = std::chrono::high_resolution_clock::now();
    deltaTime = 0;
}


void engine::Time::Update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(currentTime - startTime).count();
    startTime = currentTime;
}

float engine::Time::GetDeltaTime() {
    return deltaTime;
}
