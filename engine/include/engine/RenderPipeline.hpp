#pragma once

#include <SFML/Graphics.hpp>

namespace engine {
    class Level;
    struct RenderPipeline {
        static void draw(const Level* level, sf::RenderWindow* wnd);
    };
}
