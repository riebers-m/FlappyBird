//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <format>
#include <memory>
#include <string>

namespace game {
    class ILogger {
    public:
        virtual ~ILogger() = default;
        virtual void debug(std::string const &message) = 0;
        virtual void info(std::string const &message) = 0;
        virtual void warn(std::string const &message) = 0;
        virtual void error(std::string const &message) = 0;

        virtual void draw(std::string const &title) = 0;
    };

    class Logger {
    private:
        std::unique_ptr<ILogger> m_logger;

        template<typename... Args>
        std::string format_message(const std::format_string<Args...> fmt,
                                   Args &&...args) {
            return std::vformat(fmt.get(), std::make_format_args(args...));
        }

    public:
        explicit Logger(std::unique_ptr<ILogger> logger) :
            m_logger(std::move(logger)) {}

        /*** Brief: Logger Interface. Expects std::format formatted string to
         *forward to abstract logger
         *  https://en.cppreference.com/w/cpp/utility/format/vformat
         ****/
        template<typename... Args>
        void debug(const std::format_string<Args...> fmt, Args &&...args) {
            m_logger->debug(format_message(fmt, std::forward<Args>(args)...));
        }

        void debug(std::string const &message) { m_logger->debug(message); }

        template<typename... Args>
        void info(const std::format_string<Args...> fmt, Args &&...args) {
            m_logger->info(format_message(fmt, std::forward<Args>(args)...));
        }
        void info(std::string const &message) { m_logger->info(message); }

        template<typename... Args>
        void warn(const std::format_string<Args...> fmt, Args &&...args) {
            m_logger->warn(format_message(fmt, std::forward<Args>(args)...));
        }

        void warn(std::string const &message) { m_logger->warn(message); }

        template<typename... Args>
        void error(const std::format_string<Args...> fmt, Args &&...args) {
            m_logger->error(format_message(fmt, std::forward<Args>(args)...));
        }
        void error(std::string const &message) { m_logger->error(message); }

        void draw(std::string const &title) { m_logger->draw(title); }
    };

    using LoggerPtr = std::shared_ptr<Logger>;
} // namespace game
