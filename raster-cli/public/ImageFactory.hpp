#pragma once

#include <filesystem>
#include <fstream>

std::string load_format_id(const std::string& file_path) {
  std::ifstream in(file_path);
  if (!in.is_open()) {
    throw std::logic_error("file can not be opened for writing");
  }

  std::string format_id;
  in >> format_id;

  return format_id;
}

Image* create_image(const std::string& file_path) {
  std::string file_format = load_format_id(file_path);

  return nullptr;
}