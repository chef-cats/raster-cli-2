#pragma once

#include "P4PbmImage.hpp"

#include <filesystem>
#include <fstream>

/**
 * Reads a type ID from the first whitespace separated string in file.
 *
 * @param file_path [in] Path to file.
 * @returns The format ID of @ref file_path.
 */
static std::string load_format_id(const std::string& file_path) {
  std::ifstream in(file_path);
  if (!in.is_open()) {
    throw std::logic_error("file can not be opened for writing");
  }

  std::string format_id;
  in >> format_id;

  return format_id;
}

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