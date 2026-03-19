#include <ranges>
#include <vector>

#include <gtest/gtest.h>
#include "SFML/Graphics.hpp"

#include <engine/Engine.hpp>

namespace engine {
    class TextureManagerTest : public ::testing::Test {
        std::stringstream cerr_buffer_, sf_cerr_buffer;
        std::streambuf* old_cerr = nullptr, *old_sf_cerr = nullptr;

        void SetUp() override {
            old_cerr = std::cerr.rdbuf(cerr_buffer_.rdbuf());
            old_sf_cerr = sf::err().rdbuf(sf_cerr_buffer.rdbuf());

            TextureManager::_instance.reset(new TextureManager());
        }
        void TearDown() override {
            std::cerr.rdbuf(old_cerr);
            sf::err().rdbuf(old_sf_cerr);
        }

    public:
        const std::stringstream& get_cerr_buffer() {
            return cerr_buffer_;
        }
        const std::stringstream& get_sf_cerr_buffer() {
            return sf_cerr_buffer;
        }
        const std::map<std::string, std::weak_ptr<sf::Texture>>& get_textures_map() {
            return TextureManager::get_instance()._texture_map;
        }
    };

    TEST_F(TextureManagerTest, SuccessfulTextureLoad) {
        auto texture_ptr = TextureManager::get_instance().get_texture("hero.jpg");

        EXPECT_NE(texture_ptr, nullptr);
        EXPECT_EQ(get_cerr_buffer().str().empty(), true);
        EXPECT_EQ(get_textures_map().size(), 1);
    }
    TEST_F(TextureManagerTest, UnsuccessfulTextureLoad) {
        auto texture_ptr = TextureManager::get_instance().get_texture("unexisting.jpg");

        EXPECT_NE(texture_ptr, nullptr);
        EXPECT_EQ(get_cerr_buffer().str().empty(), false);
        EXPECT_EQ(get_textures_map().size(), 1);
    }
    TEST_F(TextureManagerTest, UsingTheSameTexture) {
        auto tex1_ptr = TextureManager::get_instance().get_texture("hero.jpg");
        auto tex2_ptr = TextureManager::get_instance().get_texture("hero.jpg");

        EXPECT_EQ(tex1_ptr, tex2_ptr);
        EXPECT_EQ(get_textures_map().at("hero.jpg").use_count(), 2);
        EXPECT_EQ(get_textures_map().size(), 1);
    }

    TEST_F(TextureManagerTest, UnloadingWhenUnused) {
        {
            auto texture_ptr = TextureManager::get_instance().get_texture("hero.jpg");
        }

        EXPECT_EQ(get_textures_map().size(), 1);
        EXPECT_EQ(get_textures_map().at("hero.jpg").lock() == nullptr, true );
    }
}

