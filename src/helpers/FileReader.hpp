//
// Created by Riebers on 09.02.2025.
//

#pragma once
#include <filesystem>
#include <tl/expected.hpp>

namespace game {
    class FileReader {
    public:
        static tl::expected<std::string, std::string> read_file(std::filesystem::path const &file);
    };
} // game
