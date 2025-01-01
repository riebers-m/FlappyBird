//
// Created by riebers on 16.12.2024.
//

#pragma once
#include <SDL_render.h>
#include <functional>
#include <vector>
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

namespace game {

    class ImGuiRender {
    private:
        SDL_Renderer *m_renderer;
        std::vector<std::function<void()>> m_func;

        // std::remove_pointer<F>::type as the type since functions are
        // converted to pointers to functions when passing by value
        template<typename T>
        static constexpr bool is_a_function = std::is_invocable_v<T>;
        // std::is_function_v<std::remove_pointer<T>>;

    public:
        template<typename... TArgs>
        explicit ImGuiRender(SDL_Renderer *renderer, TArgs &&...args) :
            m_renderer(renderer), m_func() {
            static_assert((is_a_function<TArgs> && ...),
                          "TArg is not a function");
            (m_func.emplace_back(std::forward<TArgs>(args)), ...);

            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
        }
        ~ImGuiRender() {
            for (auto &func: m_func) {
                func();
            }

            ImGui::Render();
            ImGuiIO const &io = ImGui::GetIO();
            SDL_RenderSetScale(m_renderer, io.DisplayFramebufferScale.x,
                               io.DisplayFramebufferScale.y);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),
                                                  m_renderer);
        }
    };

} // namespace game
