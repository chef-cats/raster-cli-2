#include <PbmImage.hpp>

PbmImage::PbmImage(const std::string& file_path) : NetpbmImage(file_path) {}

bool PbmImage::is_loaded() const {
  return NetpbmImage::is_loaded() && _pixels;
}

PbmImage::Color PbmImage::get_pixel(size_t width, size_t height) const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  const auto& pixels = _pixels.get();

  const size_t index = width / (CHAR_BIT * sizeof(unsigned char));
  const size_t indent = width % (CHAR_BIT * sizeof(unsigned char));

  const unsigned char mask = (1 << indent);

  unsigned char pixel = pixels.at(height).at(index) & mask;
  return pixel ? Color::BLACK : Color::WHITE;
}

void PbmImage::set_pixel(Color color, unsigned char width, unsigned char height) {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  auto& pixels = _pixels.get();

  const size_t index = width / (CHAR_BIT * sizeof(unsigned char));
  const size_t indent = width % (CHAR_BIT * sizeof(unsigned char));

  unsigned char& pixels_chunk = pixels.at(height).at(index);
  const unsigned char mask = (1 << indent);

  if (color == Color::BLACK) {
    pixels_chunk |= mask;
  } else {
    pixels_chunk &= ~mask;
  }
}