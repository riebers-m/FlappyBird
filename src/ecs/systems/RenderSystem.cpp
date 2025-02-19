//
// Created by Riebers on 14.02.2025.
//

#include "RenderSystem.hpp"
#include "ecs/components/Sprite.hpp"
#include "ecs/components/Transform.hpp"

namespace systems {
    RenderSystem::RenderSystem(game::LoggerPtr logger, entt::registry &registry) : BaseSystem(registry),
        m_logger(logger) {
    }

    void RenderSystem::update(const game::Renderer &renderer, game::AssetStore &store) const {
        auto const view = m_registry.view<component::Sprite, component::Transform>();
        for (const auto entity: view) {
            auto const &[sprite, transform] = view.get(entity);
            auto const texture = store.get_texture(sprite.id);
            SDL_Rect dest_rect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                static_cast<int>(sprite.src_rect.w * transform.scale.x),
                static_cast<int>(sprite.src_rect.h * transform.scale.y)
            };
            if (sprite.render_setting == component::render_settings::rect_whole) {
                renderer.render_whole_texture(texture, dest_rect);
            } else {
                renderer.render_texture(texture, sprite.src_rect, dest_rect);
            }
        }
    }
} // systems
