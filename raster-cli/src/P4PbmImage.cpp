#include <P4PbmImage.hpp>

#include "utils/Constants.hpp"

#include <fstream>
#include <iostream>

P4PbmImage::P4PbmImage(const std::string& file_path) : PBM(file_path) {}

std::ostream& P4PbmImage::write(std::ostream& out) const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  NetpbmImage::write(out);

  out << std::endl;

  return out.write((const char*)get_pixels().data(),
                   get_pixels().size() * sizeof(unsigned char));
}

std::istream& P4PbmImage::read(std::istream& in) {
  NetpbmImage::read(in);

  const size_t image_size = get_height() * get_width();
  const size_t data_size = ceil(image_size / (double)(UCHAR_BITS));

  in.seekg(0, std::istream::end);
  const long long file_size = in.tellg();
  in.seekg(file_size - data_size, std::ifstream::beg);

  std::vector<unsigned char> pixels(data_size);
  in.read((char*)pixels.data(), pixels.size());

  set_pixels(pixels);

  return in;
}