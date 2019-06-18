#pragma once

#include "PbmMono.hpp"

#include <fstream>

template <typename UnsignedInteger>
unsigned char find_highest_bit_position() {
  UnsignedInteger i = 1;
  unsigned char position = 0;

  while (i != 0) {
    i <<= 1;
    ++position;
  }

  return position - 1;
}

class PbmMonoBin final : public PbmMono {
public:
  PbmMonoBin(const std::string& file_path) : PbmMono(file_path) {}

  ///  @todo rename
  std::ostream& output(std::ostream& out) const override {
    if (!_pixels) {
      throw std::logic_error("file not loaded");
    }

    PbmImage::output(out);

    const auto& pixels = _pixels.get();

    const unsigned char default_mask = 1 << find_highest_bit_position<unsigned char>();

    unsigned char buffer = 0;
    unsigned char mask = default_mask;

    for (size_t row = 0; row < get_height(); ++row) {
      for (size_t col = 0; col < get_width(); ++col) {
        if (pixels[row][col]) {
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

  std::istream& input(std::istream& in) override {
    PbmImage::input(in);

    const unsigned char default_mask = 1 << find_highest_bit_position<unsigned char>();

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