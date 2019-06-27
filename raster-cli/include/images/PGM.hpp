#pragma once
#include "Netpbm.hpp"
#include <operations/Load.hpp>
#include <vector>

using PGMPixel = char;

/**
 * Images with PGM format.
 *
 * This class represents an Portable GrayMap images.
 * These are grayscale images which have defined range of possible
 * values betwee black and white - [0, max_value]. Black is 0 and
 * max_value is white. The possible values for max_value are into the
 * [1, 255].
 */

class PGM : public Netpbm {
public:
  PGM(const std::string& file_name);
  PGM(const PGM& other) = default;
  PGM(PGM&& other) = default;
  PGM& operator=(const PGM& rhs) = default;
  PGM& operator=(PGM&& rhs) = default;
  virtual ~PGM() = default;

public:
  virtual void apply(const Operation& operation) override;

public:
  PGMPixel get_pixel(size_t row, size_t column) const;
  void set_pixel(PGMPixel pixel, size_t row, size_t column);

protected:
  friend class Load;
  void allocate_pixels();

private:
  size_t _max_value;
  std::vector<std::vector<PGMPixel>> _pixels;
};
