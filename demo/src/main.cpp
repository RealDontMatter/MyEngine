#include <utility>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <engine/Engine.hpp>

#include "../include/EnemyLogic.hpp"
#include "PlayerMovement.hpp"

using namespace engine;
using namespace sf;
using namespace std;


namespace engine {
    class  Application {
        int _screen_width = 800, _screen_height = 600;
        string _title;
        unique_ptr<RenderWindow> _wnd;
        unique_ptr<Scene> _scene;
    public:
        Application(const int width, const int height, string title)
            : _screen_width(width)
            , _screen_height(height)
            , _title(std::move(title))
        {
            _wnd = make_unique<RenderWindow>(VideoMode({800, 600}), _title);
            _scene = make_unique<Scene>();
        }

        void run() {
            Time::Init();
            _scene->init();

            while (_wnd->isOpen()) {
                while (const optional event = _wnd->pollEvent()) {
                    if (event->is<Event::Closed>()) _wnd->close();
                }

                Time::Update();

                _scene->update();
                _wnd->clear();
                RenderPipeline::draw(_scene.get(), _wnd.get());
                _wnd->display();
            }
        }

        void add_objects_to_scene(std::vector<unique_ptr<GameObject>>& objects) const {
            for (auto& object : objects)
                _scene->add_object(std::move(object));
        }


    };
}

vector<unique_ptr<GameObject>> createGameObjects() {
    vector<unique_ptr<GameObject>> objects;

    /*auto player = GameObject::Create("player");
    player->GetComponent<components::Transform>()
    ->set_data({0,0,0}, {0,0,0}, {1,1,1});

    player->add_component<components::Sprite>()->set_data("hero.png", 16.f);
    player->add_component<PlayerMovement>()->set_data(10.f);*/

    auto enemy1 = GameObject::Create("enemy1");
    enemy1->add_component<components::Sprite>()->set_data("../assets/enemy.png", 16.f);
    // enemy1->add_component<EnemyLogic>()->set_data(player.get(), 8.f);
    enemy1->GetComponent<components::Transform>()->set_data({0,0,0}, {0,0,0}, {1,1,1});

    auto enemy2 = GameObject::Create("enemy2");
    enemy2->add_component<components::Sprite>()->set_data("../assets/enemy.png", 16.f);
    // enemy2->add_component<EnemyLogic>()->set_data(player.get(), 8.f);
    enemy2->GetComponent<components::Transform>()->set_data({4,0,0}, {0,0,0}, {1,1,1});

    auto camera = GameObject::Create("camera");
    camera->add_component<components::Camera>()->set_data(25);
    camera->GetComponent<components::Transform>()->set_data({0,0,0}, {0,0,0}, {1,1,1});

    // objects.push_back(std::move(player));
    objects.push_back(std::move(enemy1));
    objects.push_back(std::move(enemy2));
    objects.push_back(std::move(camera));

    return objects;
}



int main() {

    auto* app = new Application(800, 600, "demo");

    auto objs = createGameObjects();
    app->add_objects_to_scene(objs);
    app->run();

    delete app;

    return 0;
}
