#include <images/PGM.hpp>
#include <utils/Formatter.hpp>

PGM::PGM(const std::string& file_name) : Netpbm(file_name) {}

/**
 * Get pixel with coordinates row and column of the image
 *
 * @throw std::out_of_range - if row values is bigger than image's height
 *                            or column values is bigger than image's width
 * @throw std::logic_error - if the image is not loaded.
 */
PGMPixel PGM::get_pixel(size_t row, size_t column) const {
  Netpbm::metadata_check();

  return _pixels[row][column];
}

/**
 * Set new value of the pixel with coordinates row and column
 *
 * @throw std::out_of_range - if row values is bigger than image's height
 *                            or column values is bigger than image's width
 * @throw std::range_error - if the the pixel value which try to set is bigger than the
 *                           maximum possible value of the pixels for this image
 *                           (numbers of grey between black and white).
 * @throw std::logic_error - if the image is not loaded.
 */
void PGM::set_pixel(PGMPixel pixel, size_t row, size_t column) {
  Netpbm::metadata_check();

  size_t value = static_cast<size_t>(pixel);
  if (value > get_max_value()) {
    throw std::range_error(Formatter()
                           << "Try to set invalid value to " << get_file_path()
                           << ". The max value is " << static_cast<int>(get_max_value())
                           << "but you try to set " << static_cast<int>(pixel) << "!");
  }
  _pixels[row][column] = pixel;
}

size_t PGM::get_max_value() const {
  metadata_check();
  return _max_value.get();
}

void PGM::metadata_check() const {
  Netpbm::metadata_check();
  if (!_max_value) {
    throw std::logic_error(
        Formatter() << "The max value is not load, but the other metadata is. File: "
                    << get_file_path());
  }
}

/**
 * throw std::logic_error - when you try to change the max value for the second time
 */
void PGM::set_max_value(size_t max_value) {
  if (_max_value) {
    throw std::logic_error(Formatter()
                           << "The max value is already set. File: " << get_file_path());
  } else {
    _max_value = max_value;
  }
}

std::vector<std::vector<PGMPixel>>& PGM::get_pixels() {
  return _pixels;
}