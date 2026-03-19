#include <engine/RenderPipeline.hpp>

#include "engine/GameObject.hpp"
#include "engine/Scene.hpp"
#include "engine/components/Camera.hpp"
#include "engine/components/Sprite.hpp"
#include "engine/components/Transform.hpp"


void engine::RenderPipeline::draw(const Scene* scene, sf::RenderWindow* wnd) {
    GameObject* cam_obj = nullptr;
    components::Camera* cam_comp = nullptr;
    components::Transform* cam_trn = nullptr;

    for (auto object: scene->get_objects()) {
        if (object->GetComponent<components::Camera>() != nullptr) {
            cam_obj = object;
            cam_comp = object->GetComponent<components::Camera>();
            cam_trn = object->GetComponent<components::Transform>();
            break;
        }
    }
    if (cam_obj == nullptr || cam_comp == nullptr || cam_trn == nullptr) return;


    const Vector3& cam_pos = cam_trn->getPosition();

    float
        cam_width = cam_comp->getSize(),
        cam_height = cam_width * 0.75f,
        cam_mod_width = 800.f / cam_width,
        cam_mod_height = 600.f / cam_height;
    Vector3
        cs = cam_pos - Vector3(cam_width / 2, cam_height / 2, 0),
        ce = cam_pos + Vector3(cam_width / 2, cam_height / 2, 0);

    for (const auto object : scene->get_objects()) {
        auto* sprite_component = object->GetComponent<components::Sprite>();
        auto* transform_component = object->GetComponent<components::Transform>();
        if (!sprite_component || !transform_component) return;

        const sf::Texture* sf_texture =  sprite_component->get_texture();
        sf::Vector2u tex_size = sf_texture->getSize();

        float obj_dens = sprite_component->get_density();
        const Vector3& obj_pos = transform_component->getPosition();
        const Vector3& obj_rot = transform_component->getRotation();
        const Vector3& obj_sca = transform_component->getScale();
        const Vector3& obj_size = Vector3((float)tex_size.x / obj_dens * obj_sca.x, (float)tex_size.y / obj_dens * obj_sca.y, 0);

        Vector3
            ps = obj_pos - obj_size / 2,
            pe = obj_pos + obj_size / 2,
            cps = ps - cs, cpe = ps - ce;


        sf::Vector2f cam_tex_size = {obj_size.x * cam_mod_width, obj_size.y * cam_mod_height};

        const sf::Texture& tex = *sf_texture;
        sf::Sprite sf_sprite(tex);
        sf_sprite.setScale({cam_tex_size.x / tex_size.x, cam_tex_size.y / tex_size.y});
        sf_sprite.setRotation(sf::radians(obj_rot.z));
        sf_sprite.setPosition({cps.x * cam_mod_width, cps.y * cam_mod_height});

        wnd->draw(sf_sprite);
    }
}
