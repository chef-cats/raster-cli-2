#include <images/PGM.hpp>
#include <utils/Formatter.hpp>

PGM::PGM(const std::string& file_name) : Netpbm(file_name) {}

void PGM::apply(const Operation& operation) {
  operation.apply_to(*this);
}

/**
 * Get pixel with coordinates row and column of the image
 *
 * @throw std::out_of_range - if row values is bigger than image's height
 *                            or column values is bigger than image's width
 * @throw std::logic_error - if the image is not loaded.
 */
PGMPixel PGM::get_pixel(size_t row, size_t column) const {
  Netpbm::load_check();

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
  Netpbm::load_check();

  size_t value = static_cast<size_t>(pixel);
  if (value > _max_value) {
    throw std::range_error(Formatter()
                           << "Try to set invalid value to " << get_file_path()
                           << ". The max value is " << static_cast<int>(_max_value)
                           << "but you try to set " << static_cast<int>(pixel) << "!");
  }
  _pixels[row][column] = pixel;
}

size_t PGM::get_max_value() const {
  return _max_value;
}

/**
 * Allocate pixels after the metadata is loaded.
 * This method is invoked by Load operation.
 *
 * @throws std::logic_error - if you invoke this function
 *                            loading of the metadata.
 */
void PGM::allocate_pixels() {
  size_t row_cnt = get_height();
  size_t col_size = get_width();

  _pixels.resize(row_cnt);
  for (std::vector<PGMPixel>& row : _pixels) {
    row.resize(col_size);
  }
}
/**
 * @throws std::range_error - if you change to set max_value bigger than 255
 *                            @see PGM standard
 */
void PGM::set_max_value(size_t max_value) {
  static const size_t max_possible_value = 255;
  if (max_value > max_possible_value) {
    throw std::range_error(
        Formatter() << "The max possible max_value for PGM is " << max_possible_value
                    << " but you try to set it to " << max_value << "!");
  }
  _max_value = max_value;
}
