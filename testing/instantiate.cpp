
#include <gtest/gtest.h>

#include "engine/Engine.hpp"

namespace engine {
    class InstantiateTest : public ::testing::Test {

    };

    TEST_F(InstantiateTest, CloningTest) {
        auto *scene = SceneManager::create_scene();

        auto prefab = GameObject::Create("prefab");
        auto *obj = Component::Instantiate(prefab.get());

        scene->update();

        EXPECT_EQ(scene->get_objects().size(), 1);
        EXPECT_NE(obj, prefab.get());
        EXPECT_NE(prefab->get_all_components()[0], obj->get_all_components()[0]);
    }

    TEST_F(InstantiateTest, Test) {
        auto *scene = SceneManager::create_scene();

        auto prefab = GameObject::Create("prefab");
        auto *obj1 = Component::Instantiate(prefab.get());
        auto *obj2 = Component::Instantiate(prefab.get());

        scene->update();

        EXPECT_EQ(scene->get_objects().size(), 2);
        EXPECT_NE(obj1, obj2);

        EXPECT_NE(prefab->get_all_components()[0], obj1->get_all_components()[0]);


        EXPECT_EQ(obj1->get_all_components().size(), obj2->get_all_components().size());
        EXPECT_NE(obj1->get_all_components()[0], obj2->get_all_components()[0]);

    }
}
