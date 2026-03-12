
#include <gtest/gtest.h>

#include <engine/Engine.hpp>

namespace engine {
    class GameObject;

    class GameObjectTest : public ::testing::Test {

    };

    TEST_F(GameObjectTest, ConstructorInitializesCorrectly) {
        const auto obj = GameObject::Create("Player", "Actor");

        EXPECT_EQ(obj->getName(), "Player");
        EXPECT_EQ(obj->getTag(), "Actor");
        EXPECT_EQ(obj->getParent(), nullptr);
        EXPECT_TRUE(obj->getChildren().empty());
    }

    TEST_F(GameObjectTest, SettersUpdateValues) {
        const auto obj = GameObject::Create("OldName", "OldTag");

        obj->setName("NewName");
        obj->setTag("NewTag");

        EXPECT_EQ(obj->getName(), "NewName");
        EXPECT_EQ(obj->getTag(), "NewTag");
    }

    // --- Relationship Tests ---

    TEST_F(GameObjectTest, AddChildUpdatesHierarchy) {
        auto parent = GameObject::Create("Parent");
        auto child = GameObject::Create("Child");

        const auto childPtr = child.get();

        parent->addChild(std::move(child));

        EXPECT_EQ(parent->getChildren().size(), 1);
        EXPECT_TRUE(parent->has_child(childPtr));


        EXPECT_EQ(childPtr->getParent(), parent.get());
    }
    TEST_F(GameObjectTest, RemoveChildUpdatesHierarchy) {
        auto parent = GameObject::Create("Parent");
        auto child = GameObject::Create("Child");
        auto childPtr = child.get();

        parent->addChild(std::move(child));
        ASSERT_EQ(parent->getChildren().size(), 1);

        child = parent->remove_child(childPtr);

        EXPECT_TRUE(parent->getChildren().empty());
        EXPECT_FALSE(parent->has_child(childPtr));
    }

    // --- Edge Cases ---
    TEST_F(GameObjectTest, HandlesMultipleChildren) {
        auto parent = GameObject::Create("Parent");
        auto
            c1 = GameObject::Create("C1"),
            c2 = GameObject::Create("C2"),
            c3 = GameObject::Create("C3");

        auto
            c1Ptr = c1.get(),
            c2Ptr = c2.get(),
            c3Ptr = c3.get();

        parent->addChild(std::move(c1));
        parent->addChild(std::move(c2));
        parent->addChild(std::move(c3));

        EXPECT_EQ(parent->getChildren().size(), 3);
        EXPECT_EQ(parent->getChildren()[0], c1Ptr);
        EXPECT_EQ(parent->getChildren()[1], c2Ptr);
        EXPECT_EQ(parent->getChildren()[2], c3Ptr);
    }

    TEST_F(GameObjectTest, OwnershipTransfer) {
        auto        child = GameObject::Create("Child");
        auto    oldParent = GameObject::Create("Old Parent");
        auto    newParent = GameObject::Create("New Parent");

        auto childPtr = child.get();

        oldParent->addChild(std::move(child));
        GameObject::Transfer(childPtr, oldParent.get(), newParent.get());

        EXPECT_EQ(oldParent->getChildren().size(), 0);
        EXPECT_EQ(newParent->getChildren().size(), 1);
        EXPECT_EQ(newParent->getChildren()[0], childPtr);
    }

    TEST_F(GameObjectTest, HaveTransformComponent) {
        auto obj = GameObject::Create("obj");

        EXPECT_NE(obj->GetComponent<components::Transform>(), nullptr);
        EXPECT_EQ(obj->get_all_components().size(), 1);
    }
}
