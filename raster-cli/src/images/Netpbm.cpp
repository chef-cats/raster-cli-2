#include <images/Netpbm.hpp>
#include <utils/Formatter.hpp>

#include <operations/Operation.hpp>

Netpbm::Netpbm(const std::string& file_path) : Image(file_path) {}

/**
 * Outputs image's data to a stream.
 *
 * @see metadata_check
 */
std::ostream& Netpbm::write(std::ostream& out) const {
  metadata_check();

  return out << get_format_id() << get_width() << get_height();
}

/**
 * Reads image's data from a stream.
 */
std::istream& Netpbm::read(std::istream& in) {
  std::string format_id;
  in >> format_id;
  set_format_id(format_id);

  size_t width;
  in >> width;
  set_width(width);

  size_t height;
  in >> height;
  set_height(height);

  return in;
}

/**
 * Kind of an assertion. Checks if the image is loaded.
 *
 * @throws std::logic_error - if the image is not loaded.
 */
void Netpbm::metadata_check() const {
  std::string message = Formatter()
                        << "Image metadata" << get_file_path() << " is not loaded!";
  if (!_format_id) {
    throw std::logic_error("Format id " + message);
  } else if (!_width) {
    throw std::logic_error("Width " + message);
  } else if (!_height) {
    throw std::logic_error("Height " + message);
  }
}

void Netpbm::load_check() const {
  Netpbm::metadata_check();
}

/**
 * Get the magic number which represent the format of the image
 *
 * @throws std::logic_error - if the image is not loaded.
 */
const std::string& Netpbm::get_format_id() const {
  metadata_check();

  return _format_id.get();
}

/// @see metadata_check
const size_t Netpbm::get_width() const {
  metadata_check();

  return _width.get();
}

/// @see metadata_check
const size_t Netpbm::get_height() const {
  metadata_check();

  return _height.get();
}

/**
 * Set the magic number which represent the format of the image
 */
void Netpbm::set_format_id(const std::string& format_id) {
  _format_id = format_id;
}

void Netpbm::set_width(size_t width) {
  _width = width;
}

void Netpbm::set_height(size_t height) {
  _height = height;
}