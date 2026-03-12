#pragma once
#include <memory>

namespace engine {
    class Scene;
    class SceneManager {
        static std::unique_ptr<Scene> _active_scene;
        public:
            static void create_scene(const std::string& name);

    };
}