//
// Created by Riebers on 09.02.2025.
//

#include "FileReader.hpp"

#include <fstream>

namespace game {
    tl::expected<std::string, std::string> FileReader::read_file(std::filesystem::path const &path_to_file) {
        std::ifstream file{path_to_file};
        if (!file.is_open()) {
            return tl::unexpected{std::format("Could not read asset file for path: {}", path_to_file.string())};
        }
        std::string content;
        file.seekg(0, std::ios::end);
        content.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
        // istreambuf_iterator is a single-pass input iterator that reads successive characters from the
        // std::basic_streambuf object for which it was constructed.
        content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return content;
    }
} // game
