//
// Created by Riebers on 18.02.2025.
//

#include "MovementSystem.hpp"

#include "ecs/components/RigidBody.hpp"
#include "ecs/components/Sprite.hpp"
#include "ecs/components/Transform.hpp"
#include "gamer/Window.hpp"

namespace systems {
    MovementSystem::MovementSystem(game::LoggerPtr logger,
                                   entt::registry &registry) :
        BaseSystem(registry), m_logger(logger) {}

    void MovementSystem::update(game::Window const &world,
                                std::chrono::milliseconds const &dt) const {
        auto view = m_registry.view<component::Transform, component::RigidBody,
                                    component::Sprite>();

        for (auto entity: view) {
            auto [transform, rigidbody, sprite] = view.get(entity);
            transform.position += (rigidbody.velocity *
                                   std::chrono::duration<float>(dt).count());

            // check for world boundaries
            auto const world_boundaries = world.size();
            transform.position.x =
                    (transform.position.x < 0) ? 0 : transform.position.x;
            transform.position.y =
                    (transform.position.y < 0) ? 0 : transform.position.y;
            transform.position.x =
                    ((transform.position.x +
                      static_cast<float>(sprite.src_rect.w)) >
                     static_cast<float>(world_boundaries.width))
                            ? (static_cast<float>(world_boundaries.width) -
                               static_cast<float>(sprite.src_rect.w))
                            : transform.position.x;
            transform.position.y =
                    ((transform.position.y +
                      static_cast<float>(sprite.src_rect.h)) >
                     static_cast<float>(world_boundaries.height))
                            ? (static_cast<float>(world_boundaries.height) -
                               static_cast<float>(sprite.src_rect.h))
                            : transform.position.y;
        }
    }
} // namespace systems
