#pragma once
#include <memory>
#include <vector>

namespace engine {
    class Level;
    class LevelManager {
        std::vector<std::unique_ptr<Level>> _levels;
        Level* _active_level = nullptr;

        static std::unique_ptr<LevelManager> _instance;
        LevelManager() = default;

    public:
        static Level* create_level(bool active = true);
        static std::vector<Level*> get_levels();
        static Level* get_active_level();
        static void set_active_level(Level* level);
        static LevelManager* get_instance();

        LevelManager& operator=(const LevelManager&) = delete;
    };
}
