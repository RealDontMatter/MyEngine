#include <algorithm>
#include <memory>

#include <engine/LevelManager.hpp>
#include <engine/Level.hpp>
#include <engine/GameObject.hpp>
#include <engine/Component.hpp>

using namespace std;

unique_ptr<engine::LevelManager> engine::LevelManager::_instance;

engine::Level *engine::LevelManager::create_level(const bool active) {
    auto instance = get_instance();
    instance->_levels.push_back(make_unique<Level>());
    Level *level = instance->_levels.back().get();
    if (active || instance->_active_level == nullptr) {
        instance->_active_level = level;
    }
    return level;
}

vector<engine::Level *> engine::LevelManager::get_levels() {
    auto instance = get_instance();
    vector<Level *> levels;
    levels.reserve(instance->_levels.size());
    ranges::transform(
        instance->_levels.begin(),
        instance->_levels.end(),
        back_inserter(levels),
        [](auto &&level) { return level.get(); }
    );
    return levels;
}

engine::Level *engine::LevelManager::get_active_level() {
    return get_instance()->_active_level;
}

void engine::LevelManager::set_active_level(Level *level) {
    auto instance = get_instance();
    auto it = ranges::find_if(
        instance->_levels,
        [level](auto &&itLevel) { return itLevel.get() == level; }
    );
    if (it != instance->_levels.end()) {
        instance->_active_level = level;
    }
}

engine::LevelManager *engine::LevelManager::LevelManager::get_instance() {
    if (_instance == nullptr) {
        auto *instance = new LevelManager();
        _instance = unique_ptr<LevelManager>(instance);
    }
    return _instance.get();
}
