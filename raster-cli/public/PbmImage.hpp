#pragma once

#include "NetpbmImage.hpp"

#include <vector>

class PbmImage : public NetpbmImage {
public:
  PbmImage(const std::string& file_path) : NetpbmImage(file_path) {}

  enum class Color : bool { BLACK, WHITE };

  Color get_pixel(size_t width, size_t height) const {
    if (!is_loaded()) {
      throw std::logic_error("file not loaded");
    }

    size_t index = width / (CHAR_BIT * sizeof(unsigned char));
    size_t indent = width % (CHAR_BIT * sizeof(unsigned char));
    unsigned char mask = (1 << indent);

    unsigned char pixel = _pixels.get().at(height).at(index) & mask;
    return pixel ? Color::BLACK : Color::WHITE;
  }

  void set_pixel(Color color, unsigned char width, unsigned char height) {
    if (!is_loaded()) {
      throw std::logic_error("file not loaded");
    }

    size_t index = width / (CHAR_BIT * sizeof(unsigned char));
    size_t indent = width % (CHAR_BIT * sizeof(unsigned char));

    unsigned char& pixels_chunk = _pixels.get().at(height).at(index);
    unsigned char mask = (1 << indent);

    if (color == Color::BLACK) {
      pixels_chunk |= mask;
    } else {
      pixels_chunk &= ~mask;
    }
  }

  DelayLoad<std::vector<std::vector<unsigned char>>> _pixels;
};