#include <PbmImage.hpp>

#include <Operation.hpp>

PbmImage::PbmImage(const std::string& file_path) : Image(file_path) {}

void PbmImage::apply(const Operation& operation) {
  operation.apply_to(*this);
}

std::ostream& PbmImage::output(std::ostream& out) const {
  return out << get_format_id() << get_width() << get_height();
}

std::istream& PbmImage::input(std::istream& in) {
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

bool PbmImage::is_loaded() const {
  /// @todo Optimize
  return _format_id && _width && _height;
}

const std::string& PbmImage::get_format_id() const {
  if (!is_loaded()) {
    throw std::logic_error("file not loaded");
  }

  return _format_id.get();
}

const size_t PbmImage::get_width() const {
  if (!is_loaded()) {
    throw std::logic_error("file not loaded");
  }

  return _width.get();
}

const size_t PbmImage::get_height() const {
  if (!is_loaded()) {
    throw std::logic_error("file not loaded");
  }

  return _height.get();
}

void PbmImage::set_format_id(const std::string& format_id) {
  _format_id = format_id;
}

void PbmImage::set_width(size_t width) {
  _width = width;
}

void PbmImage::set_height(size_t height) {
  _height = height;
}