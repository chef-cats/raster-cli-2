#include <Save.hpp>

#include <PbmImage.hpp>

#include <fstream>

void Save::apply_to(PbmImage& image) const {
  std::ofstream out(image._file_path);
  if (!out.is_open()) {
    throw std::logic_error("file can not be opened for writing");
  }

  image.output(out);
}