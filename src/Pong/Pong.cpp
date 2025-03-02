//
// Created by Riebers on 23.02.2025.
//

#include "Pong.hpp"

#include "ecs/components/RigidBody.hpp"
#include "ecs/components/Sprite.hpp"
#include "ecs/components/Transform.hpp"
#include "gamer/EngineConfiguration.hpp"

void pong::Pong::setup() {
    auto const config = game::load_config();
    m_asset_store.load_from_file(config.assetDirectory, m_renderer); {
        auto entity = ecs::Entity::create(m_registry);
        entity.add_component<component::Sprite>("pong-sheet", 50, 110, 0, 20,
                                                component::render_settings::rect_section);
        entity.add_component<component::Transform>(glm::vec2{200, 700});
        entity.add_component<component::RigidBody>(glm::vec2{0, 50});
    }

    auto const scripts = m_asset_store.


}
