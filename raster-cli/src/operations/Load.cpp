#include <operations/Load.hpp>
#include <operations/LoadImpl.hpp>
#include <images/PGM.hpp>
#include <utils/Formatter.hpp>
#include <cstdint>


/**
 * @throws std::logic_error - if there is not implemented method which read the
 *                            image with these magic number
 */
void Load::apply_to(PGM& image) const {
  std::ifstream file(image.get_file_path());
  if (!file) {
    throw std::ios_base::failure((Formatter() << "File: " << image.get_file_path(),
                                 "can not be open!"));
  }

  load_meta_data(image, file);

  const std::string image_format = image.get_format_id();
  const uint64_t bytes_to_read = ((uint64_t)image.get_height()) * image.get_width();

  if (image_format == "P2") {
    read_from_text_file(image, bytes_to_read, file);
  } else if (image_format == "P5") {
    read_from_binary_file(image, bytes_to_read, file);
  } else {
    throw std::logic_error(
        Formatter()
        << "There is no an avaible method to read PGM image with magic number "
        << image_format << "!");
  }

  file.clear();
  file.close();
}

void Load::load_meta_data(PGM& image, std::ifstream& file) const {
  load_meta_data<Netpbm>(image, file);


}
