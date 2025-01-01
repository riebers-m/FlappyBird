//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "Logger.hpp"

namespace game {
    class ImGuiLogWindow : public ILogger {
        struct AppLog;

    private:
        std::unique_ptr<AppLog> m_logger;

    public:
        ImGuiLogWindow();

        ~ImGuiLogWindow();

        void debug(const std::string &message) override;

        void info(const std::string &message) override;

        void warn(const std::string &message) override;

        void error(const std::string &message) override;

        void draw(std::string const &title) override;
    };
} // game
