#include <utility>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <engine/Engine.hpp>

#include "EnemySpawner.hpp"
#include "../include/EnemyLogic.hpp"
#include "PlayerMovement.hpp"

using namespace engine;
using namespace sf;
using namespace std;

unique_ptr<GameObject> enemy_prefab;

namespace engine {
    class  Application {
        int _screen_width = 800, _screen_height = 600;
        string _title;
        unique_ptr<RenderWindow> _wnd;
        Scene* _active_scene;
    public:
        Application(const int width, const int height, string title)
            : _screen_width(width)
            , _screen_height(height)
            , _title(std::move(title))
        {
            _wnd = make_unique<RenderWindow>(VideoMode({800, 600}), _title);
            _active_scene = SceneManager::create_scene();
        }

        void run() {
            Time::Init();
            _active_scene->init();

            while (_wnd->isOpen()) {
                while (const optional event = _wnd->pollEvent()) {
                    if (event->is<Event::Closed>()) _wnd->close();
                }

                Time::Update();

                _active_scene->update();
                _wnd->clear();
                RenderPipeline::draw(_active_scene, _wnd.get());
                _wnd->display();
            }
        }

        void add_objects_to_scene(std::vector<unique_ptr<GameObject>>& objects) const {
            for (auto& object : objects)
                _active_scene->add_object(std::move(object));
        }


    };
}

vector<unique_ptr<GameObject>> createGameObjects() {
    vector<unique_ptr<GameObject>> objects;

    auto player = GameObject::Create("player");
    player->GetComponent<components::Transform>()
    ->set_data({0,0,0}, {0,0,0}, {1,1,1});

    player->add_component<components::Sprite>()->set_data("../assets/hero.png", 16.f);
    player->add_component<PlayerMovement>()->set_data(2.f);

    enemy_prefab = GameObject::Create("enemy");
    enemy_prefab->add_component<components::Sprite>()->set_data("../assets/enemy.png", 16.f);
    enemy_prefab->add_component<EnemyLogic>()->set_data(player.get(), 1.f);
    enemy_prefab->GetComponent<components::Transform>()->set_data({-5,5,0}, {0,0,0}, {1,1,1});

    auto spawner = GameObject::Create("spawner");
    spawner->add_component<EnemySpawner>()->set_data(5.f, enemy_prefab.get());

    auto camera = GameObject::Create("camera");
    camera->add_component<components::Camera>()->set_data(25);
    camera->GetComponent<components::Transform>()->set_data({0,0,0}, {0,0,0}, {1,1,1});

    objects.push_back(std::move(player));
    objects.push_back(std::move(camera));
    objects.push_back(std::move(spawner));

    return objects;
}



int main() {

    auto* app = new Application(800, 600, "demo");

    Scene* _active_scene = SceneManager::get_active_scene();
    auto objs = createGameObjects();
    for (auto& obj : objs)
        _active_scene->add_object(std::move(obj));
    app->run();

    delete app;

    return 0;
}
