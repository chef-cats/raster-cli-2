#pragma once

#include "Image.hpp"

#include <boost/optional.hpp>

#include <fstream>

/**
 * Forward declaration of NetpbmImage.
 */
class Operation;

/**
 * Image in Netpbm format.
 *
 * Holds common data for all sub-formats of Netpbm.
 * More info: <https://en.wikipedia.org/wiki/Netpbm_format>
 */
class NetpbmImage : public Image {
public:
  NetpbmImage(const std::string& file_path);

  void apply(const Operation& operation) override;

  /**
   * Outputs image's data to a stream.
   * 
   * @throw std::logic_error if image is not loaded yet.
   */
  virtual std::ostream& write(std::ostream& out) const = 0;
  /**
   * Reads image's data from a stream.
   */
  virtual std::istream& read(std::istream& in) = 0;

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
  boost::optional<std::string> _format_id; ///< ID of the format.
  boost::optional<size_t> _width;          ///< Count of pixels in a row.
  boost::optional<size_t> _height;         ///< Count of pixels in a column.
};