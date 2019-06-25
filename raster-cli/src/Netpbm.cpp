#include <Netpbm.hpp>

#include <Operation.hpp>

Netpbm::Netpbm(const std::string& file_path) : Image(file_path) {}

/**
 * Outputs image's data to a stream.
 *
 * @throw std::logic_error if image is not loaded yet.
 */
std::ostream& Netpbm::write(std::ostream& out) const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

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
void Netpbm::loadCheck() const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
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
  loadCheck();

  return _format_id.get();
}

/**
 * Get width of the image
 *
 * @throws std::logic_error - if the image is not loaded.
 */
const size_t Netpbm::get_width() const {
  loadCheck();

  return _width.get();
}

/**
 * Get height of the image
 *
 * @throws std::logic_error - if the image is not loaded.
 */
const size_t Netpbm::get_height() const {
  loadCheck();

  return _height.get();
}

void Netpbm::set_format_id(const std::string& format_id) {
  _format_id = format_id;
}

void Netpbm::set_width(size_t width) {
  _width = width;
}

void Netpbm::set_height(size_t height) {
  _height = height;
}