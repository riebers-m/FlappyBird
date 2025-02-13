//
// Created by HP on 25.12.2024.
//

#ifndef TEXT_H
#define TEXT_H
#include <functional>
#include "gamer/Context.hpp"

namespace game {
    class Text {
    public:
        // Constructor: Initializes with renderer, font, and text
        explicit Text(Context const &context, const std::string &text,
                      SDL_Rect const &rect, SDL_Color color, std::string const &id);

        void set_text(const std::string &text);

        void render() const;

        // Getters for dimensions
        [[nodiscard]] SDL_Rect get_rect() const;

        void set_color(SDL_Color color);

        void set_position(SDL_Point position);

    private:
        Context const &m_context;
        SDL_Color m_color;
        std::string m_text;

        std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)> > m_texture;
        SDL_Rect m_rect;
        std::string m_id;

        // Regenerates the SDL_Texture from the current text
        void regenerateTexture();
    };
} // game

#endif //TEXT_H
