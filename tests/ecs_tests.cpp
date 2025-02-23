//
// Created by Riebers on 25.01.2025.
//

#include <catch2/catch_all.hpp>
#include "ecs/Entity.hpp"
#include "ecs/components/RigidBody.hpp"
#include "ecs/components/Transform.hpp"

TEST_CASE("Create entity") {
    entt::registry registry;

    auto entity = ecs::Entity::create(registry);
    REQUIRE(entity.is_valid());
    entity.destroy();
    REQUIRE(entity.is_valid());
    ecs::Entity::destroy_all_entities(registry);
    REQUIRE(!entity.is_valid());
}

TEST_CASE("Add component") {
    entt::registry registry;

    SECTION("Simple") {
        auto entity = ecs::Entity::create(registry);
        auto component = entity.add_component<component::Transform>(glm::vec2{20.0, 25.0}, component::degree{10},
                                                                    glm::vec2{2.0, 2.0});
        REQUIRE(component.position.x == 20.0);
        REQUIRE(component.position.y == 25.0);
        REQUIRE(component.rotation == 10.0);
        REQUIRE(component.scale.x == 2.0);
        REQUIRE(component.scale.y == 2.0);
    }
    SECTION("Empty args") {
        auto entity = ecs::Entity::create(registry);
        auto component = entity.add_component<component::Transform>();
        REQUIRE(component.position.x == 0.0);
        REQUIRE(component.position.y == 0.0);
        REQUIRE(component.rotation == 0.0);
        REQUIRE(component.scale.x == 1.0);
        REQUIRE(component.scale.y == 1.0);
    }
}

TEST_CASE("Manipulate component") {
    entt::registry registry;

    SECTION("Simple") {
        auto entity = ecs::Entity::create(registry);
        auto rigid_body = entity.add_component<component::RigidBody>(glm::vec2{10, 20});
        REQUIRE(rigid_body.velocity.x == 10);
        REQUIRE(rigid_body.velocity.y == 20);
        auto replaced_body = entity.replace<component::RigidBody>(glm::vec2{30, 40});
        REQUIRE(replaced_body.velocity.x == 30);
        REQUIRE(replaced_body.velocity.y == 40);
    }
    SECTION("Use optional getter") {
        auto entity = ecs::Entity::create(registry);
        auto rigid_body = entity.add_component<component::RigidBody>(glm::vec2{10, 20});
        REQUIRE(rigid_body.velocity.x == 10);
        REQUIRE(rigid_body.velocity.y == 20);
        entity.replace<component::RigidBody>(glm::vec2{30, 40});
        auto const replaced_body = entity.get_optional<component::RigidBody>();
        REQUIRE(replaced_body.value().velocity.x == 30);
        REQUIRE(replaced_body.value().velocity.y == 40);
    }
    SECTION("Use reference") {
        auto entity = ecs::Entity::create(registry);
        auto &rigid_body = entity.add_component<component::RigidBody>(glm::vec2{10, 20});
        REQUIRE(rigid_body.velocity.x == 10);
        REQUIRE(rigid_body.velocity.y == 20);
        rigid_body.velocity = {100, 200};
        auto const &again = entity.get_component<component::RigidBody>();
        REQUIRE(again.velocity.x == 100);
        REQUIRE(again.velocity.y == 200);
    }
}

TEST_CASE("Has component") {
    entt::registry registry;
    SECTION("Simple") {
        auto entity = ecs::Entity::create(registry);
        REQUIRE(!entity.has_components<component::Transform, component::RigidBody>());
        entity.add_component<component::Transform>();
        REQUIRE(entity.has_components<component::Transform>());
        REQUIRE(!entity.has_components<component::RigidBody>());
        REQUIRE(!entity.has_components<component::RigidBody, component::Transform>());
    }
    SECTION("Multiple") {
        auto entity = ecs::Entity::create(registry);
        REQUIRE(!entity.has_components<component::Transform, component::RigidBody>());
        entity.add_components<component::Transform, component::RigidBody>();
        REQUIRE(entity.has_components<component::Transform, component::RigidBody>());
        REQUIRE(entity.has_components<component::Transform>());
        REQUIRE(entity.has_components<component::RigidBody>());
    }
}
