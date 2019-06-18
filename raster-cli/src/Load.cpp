#include <Load.hpp>

#include "PbmImage.hpp"

#include <fstream>

void Load::apply_to(PbmImage& image) const {
  std::ifstream in(image._file_path);
  if (!in.is_open()) {
    throw std::logic_error("file can not be opened for reading");
  }

  image.input(in);
}