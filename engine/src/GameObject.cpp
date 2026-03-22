#include <utility>
#include <algorithm>
#include <ranges>

#include <engine/GameObject.hpp>
#include <engine/Component.hpp>
#include <engine/components/Transform.hpp>

engine::GameObject::GameObject(std::string name, std::string tag) : _name(std::move(name)), _tag(std::move(tag)) {}

std::unique_ptr<engine::GameObject> engine::GameObject::Create(std::string name, std::string tag) {
    const auto rawPtr = new GameObject(std::move(name), std::move(tag));
    rawPtr->add_component<components::Transform>();
    return std::unique_ptr<GameObject>(rawPtr);
}

// Basic Properties
void engine::GameObject::setName(std::string name) { _name = std::move(name); }
void engine::GameObject::setTag(std::string tag) { _tag = std::move(tag); }
const std::string& engine::GameObject::getTag() const { return _tag; }
const std::string& engine::GameObject::getName() const { return _name; }


// GameObject - GameObject Ownership
engine::GameObject *engine::GameObject::getParent() const { return _parent; }
std::vector<engine::GameObject *> engine::GameObject::getChildren() const {
    std::vector<GameObject*> children;
    for (auto& child : _children) {
        children.push_back(child.get());
    }
    return children;
}
void engine::GameObject::addChild(std::unique_ptr<GameObject> child) {
    if (child) {
        auto childPtr = child.get();
        _children.push_back(std::move(child));
        childPtr->_parent = this;
    }
}
std::unique_ptr<engine::GameObject> engine::GameObject::remove_child(GameObject *childPtr) {
    if (childPtr == nullptr) return nullptr;
    const auto it = std::ranges::find_if(_children,
        [childPtr](const std::unique_ptr<GameObject>& ptr) {
            return ptr.get() == childPtr;
        }
    );
    if (it != _children.end()) {
        std::unique_ptr<GameObject> removed = std::move(*it);
        childPtr->_parent = nullptr;
        _children.erase(it);
        return removed;
    }
    return nullptr;
}

bool engine::GameObject::has_child(GameObject *childPtr) const {
    const auto it = std::ranges::find_if(_children,
        [childPtr](const std::unique_ptr<GameObject>& ptr) {
            return ptr.get() == childPtr;
        }
    );
    return it != _children.end();
}

void engine::GameObject::Transfer(GameObject *child, GameObject *oldParent, GameObject *newParent) {
    if (!child || !oldParent || !newParent) return;
    newParent->addChild(oldParent->remove_child(child));
}


// Component System
std::vector<engine::Component *> engine::GameObject::get_all_components() const {
    std::vector<Component*> objs;
    for (auto &comp : _components)
        objs.push_back(comp.get());
    return objs;
}
engine::components::Transform * engine::GameObject::get_transform() {
    return GetComponent<components::Transform>();
}

// Life cycle
void engine::GameObject::Update() const {
    for (const auto &comp : _components) {
        if (!comp->has_started()) {
            comp->start();
            comp->set_has_started();
        }
    }
    for (const auto &comp : _components) {
        comp->update();
    }
}

engine::GameObject::GameObject(const GameObject &other) {
    _tag = other._tag;
    _name = other._name;
    _parent = nullptr;

    _children = std::vector<std::unique_ptr<GameObject>>(other._children.size());
    for (int i = 0; i < other._children.size(); i++) {
        _children[i] = std::make_unique<GameObject>(*other._children[i]);
    }

    _components = std::vector<std::unique_ptr<Component>>(other._components.size());
    for (int i = 0; i < other._components.size(); i++) {
        _components[i] = other._components[i]->clone(); //std::make_unique<Component>(*other._components[i]);
        _components[i]->set_owner(this);
    }
}

engine::GameObject & engine::GameObject::operator=(const GameObject &other) {
    _tag = other._tag;
    _name = other._name;
    _parent = nullptr;

    _children = std::vector<std::unique_ptr<GameObject>>(other._children.size());
    for (int i = 0; i < other._children.size(); i++) {
        _children[i] = std::make_unique<GameObject>(*other._children[i]);
    }

    _components = std::vector<std::unique_ptr<Component>>(other._components.size());
    for (int i = 0; i < other._components.size(); i++) {
        _components[i] = other._components[i]->clone(); //std::make_unique<Component>(*other._components[i]);
        _components[i]->set_owner(this);
    }

    return *this;
}
