#include <algorithm>
#include <memory>

#include <engine/SceneManager.hpp>
#include <engine/Scene.hpp>
#include <engine/GameObject.hpp>
#include <engine/Component.hpp>

using namespace std;

unique_ptr<engine::SceneManager> engine::SceneManager::_instance;

engine::Scene *engine::SceneManager::create_scene(const bool active) {
    auto instance = get_instance();
    instance->_scenes.push_back(make_unique<Scene>());
    Scene *scene = instance->_scenes.back().get();
    if (active || instance->_active_scene == nullptr) {
        instance->_active_scene = scene;
    }
    return scene;
}

vector<engine::Scene *> engine::SceneManager::get_scenes() {
    auto instance = get_instance();
    vector<Scene *> scenes;
    scenes.reserve(instance->_scenes.size());
    ranges::transform(
        instance->_scenes.begin(),
        instance->_scenes.end(),
        back_inserter(scenes),
        [](auto &&scene) { return scene.get(); }
    );
    return scenes;
}

engine::Scene *engine::SceneManager::get_active_scene() {
    return get_instance()->_active_scene;
}

void engine::SceneManager::set_active_scene(Scene *scene) {
    auto instance = get_instance();
    auto it = ranges::find_if(
        instance->_scenes,
        [scene](auto &&itScene) { return itScene.get() == scene; }
    );
    if (it != instance->_scenes.end()) {
        instance->_active_scene = scene;
    }
}

engine::SceneManager *engine::SceneManager::SceneManager::get_instance() {
    if (_instance == nullptr) {
        auto *instance = new SceneManager();
        _instance = unique_ptr<SceneManager>(instance);
    }
    return _instance.get();
}
