//
// Created by riebers on 19.12.2024.
//

#pragma once
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <functional>
#include <memory>
#include "gamer/Context.hpp"


namespace game {
    class Button {
        enum class BUTTON_STATE {
            idle,
            hover,
            pressed,
        };

    public:
        explicit Button(Context, SDL_Rect const &bbox, const std::string &text,
                        std::function<void()> callback);

        void set_bbox(SDL_Rect const &new_bbox);

        void handle_events(SDL_Event const &event);

        void update();

        void render(SDL_Renderer *);

        void on_clicked(std::function<void()> callback);

        void set_text(const std::string &text, SDL_Renderer *renderer, SDL_Color color);

        [[nodiscard]] SDL_Rect size() const;

    private:
        Context m_context;
        SDL_Rect m_bbox{};
        std::string m_text;
        std::function<void()> m_callback;
        bool m_clicked{false};
        bool m_inside{false};
        BUTTON_STATE m_state{BUTTON_STATE::idle};
        std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)> > m_texture;
    };
} // namespace game
