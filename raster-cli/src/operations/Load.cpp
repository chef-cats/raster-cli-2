#include <cstdint>
#include <images/PGM.hpp>
#include <operations/Load.hpp>
#include <operations/LoadImpl.hpp>
#include <utils/Formatter.hpp>

void skip_whitespace(std::ifstream& file) {
  char symbol;
  file >> symbol;
  file.unget();
  file.clear();
}

void read_line(std::ifstream& file, std::string& result) {
  std::getline(file, result);
  skip_whitespace(file);
}

void skip_comments(std::ifstream& file, const std::string& file_name) {
  std::string buffer;
  char symbol;
  do {
    file.get(symbol);
    if (symbol == '#') {
      read_line(file, buffer);
    } else {
      file.unget();
      file.clear();
    }
    file_healthcheck(file, file_name);
  } while (symbol == '#');
}

void file_healthcheck(std::ifstream& file, const std::string& file_name) {
  if (!file.is_open()) {
    throw std::ios_base::failure(Formatter()
                                 << "The file: " << file_name << " is not open.");
  }
  if (file.fail()) {
    throw std::ios_base::failure(
        (Formatter() << "Some of the data is not into the correct type into the file: "
                     << file_name << "!"));
  }
  if (file.bad()) {
    throw std::ios_base::failure(Formatter() << "File: " << file_name
                                             << " has broken during reading");
  }
}

/**
 * @throws std::logic_error - if there is not implemented method which read the
 *                            image with these magic number
 */
void Load::apply_to(PGM& image) const {
  std::string file_name = image.get_file_path();
  std::ifstream file(file_name);
  file_healthcheck(file, file_name);

  load_meta_data(image, file);
  image.allocate_pixels();
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
  load_meta_data(static_cast<Netpbm&>(image), file);

  size_t max_value;
  file >> max_value;
  image.set_max_value(max_value);

  skip_comments(file, image.get_file_path());
  skip_whitespace(file);
  file_healthcheck(file, image.get_file_path());
}

inline void Load::load_meta_data(Netpbm& image, std::ifstream& file) const {
  std::string file_name = image.get_file_path();
  file_healthcheck(file, file_name);

  std::string buffer;

  read_line(file, buffer);
  image.set_format_id(buffer);

  skip_comments(file, file_name);

  size_t height;
  file >> height;
  image.set_height(height);

  size_t width;
  file >> width;
  image.set_width(width);

  skip_comments(file, file_name);
  skip_whitespace(file);
  file_healthcheck(file, file_name);
}