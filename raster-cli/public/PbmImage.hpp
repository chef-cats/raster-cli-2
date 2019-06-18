#pragma once

#include "Image.hpp"

#include <boost/optional.hpp>

#include <fstream>

class Operation;

class PbmImage : public Image {
public:
  PbmImage(const std::string& file_path);

  void apply(const Operation& operation) override;

  virtual std::ostream& output(std::ostream& out) const = 0;
  virtual std::istream& input(std::istream& in) = 0;

public:
  bool is_loaded() const;

  const std::string& get_format_id() const;
  const size_t get_width() const;
  const size_t get_height() const;

protected:
  void set_format_id(const std::string& format_id);
  void set_width(size_t width);
  void set_height(size_t height);

private:
  boost::optional<std::string> _format_id;
  boost::optional<size_t> _width;
  boost::optional<size_t> _height;
};