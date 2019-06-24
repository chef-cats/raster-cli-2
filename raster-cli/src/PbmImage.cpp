#include <PbmImage.hpp>

PbmImage::PbmImage(const std::string& file_path) : NetpbmImage(file_path) {}

bool PbmImage::is_loaded() const {
  return is_metadata_loaded() && _pixels;
}

PbmImage::Color PbmImage::get_pixel(size_t width, size_t height) const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  const auto& pixels = _pixels.get();

  const size_t index = width / (CHAR_BIT * sizeof(unsigned char));
  const size_t indent = width % (CHAR_BIT * sizeof(unsigned char));

  const unsigned char mask = (1 << indent);

  unsigned char pixel = pixels.at(height * get_width() + index) & mask;
  return pixel ? Color::BLACK : Color::WHITE;
}

void PbmImage::set_pixel(Color color, unsigned char width, unsigned char height) {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  auto& pixels = _pixels.get();

  const size_t index = width / (CHAR_BIT * sizeof(unsigned char));
  const size_t indent = width % (CHAR_BIT * sizeof(unsigned char));

  unsigned char& pixels_chunk = pixels.at(height * get_width() + index);
  const unsigned char mask = (1 << indent);

  if (color == Color::BLACK) {
    pixels_chunk |= mask;
  } else {
    pixels_chunk &= ~mask;
  }
}

const std::vector<unsigned char>& PbmImage::get_pixels() const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  return _pixels.get();
}

void PbmImage::set_pixels(const std::vector<unsigned char>& pixels) {
  if (!is_metadata_loaded()) {
    throw std::logic_error("Image metadata is not loaded!");
  }

  size_t bits_count = get_width() * get_height();
  if (bits_count < (pixels.size() - 1) * CHAR_BIT * sizeof(unsigned char)
      && pixels.size() * CHAR_BIT * sizeof(unsigned char) < bits_count) {
    throw std::invalid_argument("Size of image doesn't match");
  }

  _pixels = pixels;
}