#pragma once

#include "Image.hpp"

#include "utils/HelperFunctions.hpp"

/**
 * Creates the appropriate Image sub-type to represent the file.
 *
 * @param file_path [in] Path to file.
 * @returns Image* to the new object or nullptr.
 */
static Image* create_image(const std::string& file_path) {
    std::string file_format = load_format_id(file_path);

    return nullptr;
}
