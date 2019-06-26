#include <images/Netpbm.hpp>
#include <utils/Formatter.hpp>

#include <operations/Operation.hpp>

Netpbm::Netpbm(const std::string& file_path) : Image(file_path) {}

/**
 * Kind of an assertion. Checks if the image is loaded.
 *
 * @throws std::logic_error - if the image is not loaded.
 */
void Netpbm::load_check() const {
  if (!is_loaded()) {
    throw std::logic_error(Formatter()
                           << "Image " << get_file_path() << " is not loaded!");
  }
}

bool Netpbm::is_loaded() const {
  return _format_id && _width && _height;
}

/**
 * Get the magic number which represent the format of the image
 *
 * @throws std::logic_error - if the image is not loaded.
 */
const std::string& Netpbm::get_format_id() const {
  load_check();

  return _format_id.get();
}

/// @see load_check
const size_t Netpbm::get_width() const {
  load_check();

  return _width.get();
}

/// @see load_check
const size_t Netpbm::get_height() const {
  load_check();

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