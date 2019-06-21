#pragma once

#include "PbmImage.hpp"

#include <fstream>

template <typename UnsignedInteger>
unsigned char high_bit_index() {
  UnsignedInterger bits_count = (CHAR_BIT * sizeof(UnsignedInteger));

  return bits_count - 1;
}

class P4PbmImage final : public PbmImage {
public:
  P4PbmImage(const std::string& file_path) : PbmImage(file_path) {}

  std::ostream& write(std::ostream& out) const override {
    if (!is_loaded()) {
      throw std::logic_error("Image is not loaded!");
    }

    NetpbmImage::write(out);

    const unsigned char default_mask = 1 << high_bit_index<unsigned char>();

    unsigned char buffer = 0;
    unsigned char mask = default_mask;

    for (size_t row = 0; row < get_height(); ++row) {
      for (size_t col = 0; col < get_width(); ++col) {
        if (get_pixel(col, row) == Color::BLACK) {
          buffer |= mask;
        }

        mask >> 1;
        if (mask == 0) {
          out.write((const char*)&buffer, sizeof(buffer));
          mask = default_mask;
        }
      }
    }

    /// @todo Check if this is correct.
    out.write((const char*)&buffer, sizeof(buffer));

	return out;
  }

  std::istream& read(std::istream& in) override {
    NetpbmImage::read(in);

    const unsigned char default_mask = 1 << high_bit_index<unsigned char>();

    unsigned char buffer = 0;

    std::vector<std::vector<bool>> pixels;
    pixels.resize(get_height());
    for (auto& pixel_row : pixels) {
      pixel_row.resize(get_width());
    }

    /// @todo Fix this
    while (in.read((char*)&buffer, sizeof(buffer))) {
      unsigned char mask = default_mask;
      while (mask != 0) {
        if (buffer & mask) {
        }
        mask >> 1;
      }
    }
	return in;
  }
};