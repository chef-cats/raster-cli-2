#include <NetpbmImage.hpp>
#include <Operation.hpp>

#include <fstream>

NetpbmImage::NetpbmImage(const std::string& file_path) : Image(file_path) {}

void NetpbmImage::apply(const Operation& operation) {
  operation.apply_to(*this);
}

std::ostream& NetpbmImage::write(std::ostream& out) const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  return out << get_format_id() << get_width() << get_height();
}

std::istream& NetpbmImage::read(std::istream& in) {
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

bool NetpbmImage::is_loaded() const {
  return _format_id && _width && _height;
}

const std::string& NetpbmImage::get_format_id() const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  return _format_id.get();
}

const size_t NetpbmImage::get_width() const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  return _width.get();
}

const size_t NetpbmImage::get_height() const {
  if (!is_loaded()) {
    throw std::logic_error("Image is not loaded!");
  }

  return _height.get();
}

void NetpbmImage::set_format_id(const std::string& format_id) {
  _format_id = format_id;
}

void NetpbmImage::set_width(size_t width) {
  _width = width;
}

void NetpbmImage::set_height(size_t height) {
  _height = height;
}