#pragma once

#include "BinaryPGM.hpp"
#include "TextPGM.hpp"

#include "utils/HelperFunctions.hpp"

/**
 * Creates the appropriate Image sub-type to represent the file.
 *
 * @param file_path [in] Path to file.
 * @returns Image* to the new object or nullptr.
 */
static std::unique_ptr<Image> create_image(const std::string& file_path) {
    std::string file_format = load_format_id(file_path);

    if (file_format == "P2") {
        return std::make_unique<TextPGM>(file_path);
    } else if (file_format == "P5") {
        return std::make_unique<BinaryPGM>(file_path);
    }

    return nullptr;
}
