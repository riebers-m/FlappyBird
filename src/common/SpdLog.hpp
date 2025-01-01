//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "Logger.hpp"
#include "spdlog/logger.h"

namespace game {
    class Spdlogger : public ILogger {
    private:
        std::shared_ptr<spdlog::logger> m_logger;

    public:
        explicit Spdlogger(std::shared_ptr<spdlog::logger> logger) : m_logger(std::move(logger)) {}

        void debug(std::string const &message) override { m_logger->debug(message); }
        void info(std::string const &message) override { m_logger->info(message); }
        void warn(std::string const &message) override { m_logger->warn(message); }
        void error(std::string const &message) override { m_logger->error(message); }
        void draw(std::string const &title) override{};
    };
}
