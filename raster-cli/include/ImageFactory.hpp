#pragma once

#include "P4PbmImage.hpp"

#include "utils/HelperFunctions.hpp"

#include <filesystem>

/**
 * Creates the appropriate Image sub-type to represent the file.
 *
 * @todo Return std::unique_ptr<Image>.
 *
 * @param file_path [in] Path to file.
 * @returns Image* to the new object or nullptr.
 */
static Image* create_image(const std::string& file_path) {
  std::string file_format = load_format_id(file_path);

  if (file_format == "P4") {
    return new P4PbmImage(file_path);
  }

  return nullptr;
}
