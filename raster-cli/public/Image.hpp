#pragma once

#include <string>

class Operation;

class Image {
public:
  virtual ~Image() = default;

  Image(const std::string& file_path) : _file_path(file_path) {}

  virtual void apply(const Operation& operation) = 0;

  std::string _file_path;
};