#pragma once

#include <SFML/Graphics.hpp>

namespace engine {
    class Scene;
    struct RenderPipeline {
        static void draw(const Scene* scene, sf::RenderWindow* wnd);
    };
}