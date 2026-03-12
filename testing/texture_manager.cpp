#include <ranges>
#include <vector>

#include <gtest/gtest.h>
#include "SFML/Graphics/Texture.hpp"

#include <engine/Engine.hpp>

namespace engine {
    class TextureManagerTest : public ::testing::Test {
        std::stringstream buffer;
        std::streambuf* old_cerr = nullptr;

        void SetUp() override {
            old_cerr = std::cerr.rdbuf(buffer.rdbuf());
        }

        void TearDown() override {
            std::cerr.rdbuf(old_cerr);
            EXPECT_TRUE(buffer.str().empty())
                << "Test leaked data to stderr: " << buffer.str();
        }
    };
    TEST_F(TextureManagerTest, Tests) {
        sf::Texture texture = TextureManager::getTexture("enemy.png");
        EXPECT_EQ(true, true);
    }
}

