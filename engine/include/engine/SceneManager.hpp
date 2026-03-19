#pragma once
#include <memory>
#include <vector>

namespace engine {
    class Scene;
    class SceneManager {
        std::vector<std::unique_ptr<Scene>> _scenes;
        Scene* _active_scene = nullptr;

        static std::unique_ptr<SceneManager> _instance;
        SceneManager() = default;

    public:
        static Scene* create_scene(bool active = true);
        static std::vector<Scene*> get_scenes();
        static Scene* get_active_scene();
        static void set_active_scene(Scene* scene);
        static SceneManager* get_instance();

        SceneManager& operator=(const SceneManager&) = delete;
    };
}