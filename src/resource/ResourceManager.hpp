//
// Created by riebers on 19.12.2024.
//

#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>

namespace game {
    using asset_id = std::string;

    template<typename Derived, typename T>
    class ResourceManager {
    private:
        std::unordered_map<asset_id, std::shared_ptr<T> > m_resources;

    public:
        std::shared_ptr<T> get_resource(asset_id id) const {
            return m_resources.at(id);
        }

        void clear() { m_resources.clear(); }

        template<typename... Args>
        void load_resource(asset_id id, Args &&... args) {
            auto &manager = static_cast<Derived &>(*this);
            std::shared_ptr<T> resource = manager.load(std::forward<Args>(args)...);
            m_resources.emplace(id, resource);
        }

        [[nodiscard]] bool has_resource(asset_id id) const {
            return m_resources.contains(id);
        }
    };
} // namespace game
