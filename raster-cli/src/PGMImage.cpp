#include "..\include\PGMImage.hpp"


PGMImage::PGMImage(const std::string& file_name) : NetpbmImage(file_name) {}

/**
 * Get pixel with coordinates row and column of the image
 * 
 * @throw std::out_of_range - if row values is bigger than image's height
 *                            or column values is bigger than image's width
 * @throw std::logic_error - if the image is not loaded. 
 */
PGMPixel PGMImage::get_pixel(size_t row, size_t column) const {
  if (!is_metadata_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }
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
void PGMImage::set_pixel(PGMPixel pixel, size_t row, size_t column) {
  if (!is_metadata_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }
  size_t value = static_cast<size_t>(pixel);
  if (value > _max_value) {
    throw std::range_error("Try to set invalid value!");
  }
  _pixels[row][column] = pixel;
}
