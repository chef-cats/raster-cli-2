#include <operations/Load.hpp>
#include <images/PGM.hpp>
#include <utils/Formatter.hpp>
#include <utils/FileOperations.hpp>
#include <cstdint>

/**
 * @throws std::logic_error - if there is not implemented method which read the
 *                            image with these magic number
 */
void Load::apply_to(PGM& image) const {
  const std::string image_format = image.get_format_id();
  const uint64_t bytes_to_read = ((uint64_t)image.get_height()) * image.get_width();
  if (image_format == "P2") {
    read_from_text_file<PGM, PGMPixel>(image, bytes_to_read);
  } else if (image_format == "P5") {
    read_from_binary_file<PGM, PGMPixel>(image, bytes_to_read);
  } else {
    throw std::logic_error(
        Formatter()
        << "There is no an avaible method to read PGM image with magic number "
        << image_format << "!");
  }
}