#pragma once
#include "NetpbmImage.hpp"
#include <vector>

typedef char PGM_pixel;

/**
 * Images with PGM format.
 *
 * This class represents an Portable GrayMap images.
 * These are grayscale images which have defined range of possible
 * values betwee black and white - [0, max_value]. Black is 0 and 
 * max_value is white. The possible values for max_value are into the 
 * [1, 255].
 */

class PGMImage : public NetpbmImage {
public:
  PGMImage(const std::string& file_name);
  PGMImage(const PGMImage& other) = default;
  PGMImage(PGMImage&& other) = default;
  PGMImage& operator=(const PGMImage& rhs) = default;
  PGMImage& operator=(PGMImage&& rhs) = default;
  virtual ~PGMImage() = default;

public:
  PGM_pixel get_pixel(size_t row, size_t column) const;
  void set_pixel(PGM_pixel pixel, size_t row, size_t column);

private:
  static const size_t MAX_POSSIBLE_VALUE = 255;
  size_t _max_value;
  std::vector<std::vector<PGM_pixel>> _pixels;
};
