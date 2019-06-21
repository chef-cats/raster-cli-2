#pragma once

#include "NetpbmImage.hpp"

#include <vector>

class PbmImage : public NetpbmImage {
public:
  PbmImage(const std::string& file_path) : NetpbmImage(file_path) {}

public:
  bool is_loaded() const override;

  enum class Color : bool { BLACK, WHITE };

  Color get_pixel(size_t width, size_t height) const;
  void set_pixel(Color color, unsigned char width, unsigned char height);

private:
  DelayLoad<std::vector<std::vector<unsigned char>>> _pixels;
};