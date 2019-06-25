#include <PBM.hpp>

#include "utils/Constants.hpp"

struct PBMPixelPosition {
  explicit PBMPixelPosition(size_t index, size_t offset) : _index(index), _offset(offset) {}

  size_t _index;
  size_t _offset;
};

static PBMPixelPosition get_pixel_position(size_t width) {
  return PBMPixelPosition(width / UCHAR_BITS, width % UCHAR_BITS);
}

PBM::PBM(const std::string& file_path) : NetpbmImage(file_path) {}

bool PBM::is_loaded() const {
  return is_metadata_loaded() && _pixels;
}

PBM::Color PBM::get_pixel(size_t width, size_t height) const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  const auto pixel_position = get_pixel_position(width);
  const unsigned char mask = (1 << pixel_position._offset);

  const auto& pixels = _pixels.get();
  unsigned char pixel = pixels.at(height * get_width() + pixel_position._index) & mask;
  return pixel ? Color::BLACK : Color::WHITE;
}

void PBM::set_pixel(Color color, unsigned char width, unsigned char height) {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  const auto pixel_position = get_pixel_position(width);
  const unsigned char mask = (1 << pixel_position._offset);

  auto& pixels = _pixels.get();
  unsigned char& pixels_chunk = pixels.at(height * get_width() + pixel_position._index);

  if (color == Color::BLACK) {
    pixels_chunk |= mask;
  } else {
    pixels_chunk &= ~mask;
  }
}

const std::vector<unsigned char>& PBM::get_pixels() const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  return _pixels.get();
}

void PBM::set_pixels(const std::vector<unsigned char>& pixels) {
  if (!is_metadata_loaded()) {
    throw std::logic_error("Image metadata is not loaded!");
  }

  size_t bits_count = get_width() * get_height();
  if (bits_count < (pixels.size() - 1) * UCHAR_BITS
      && pixels.size() * UCHAR_BITS < bits_count) {
    throw std::invalid_argument("Size of image doesn't match");
  }

  _pixels = pixels;
}