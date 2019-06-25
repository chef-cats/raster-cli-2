#pragma once

#include "NetpbmImage.hpp"

#include <vector>

class PBM : public NetpbmImage {
public:
  PBM(const std::string& file_path);

public:
  virtual bool is_loaded() const;

  enum class Color : bool { BLACK, WHITE };

  Color get_pixel(size_t width, size_t height) const;
  void set_pixel(Color color, unsigned char width, unsigned char height);

protected:
  const std::vector<unsigned char>& get_pixels() const;
  void set_pixels(const std::vector<unsigned char>& pixels);

private:
  DelayLoad<std::vector<unsigned char>> _pixels;
};