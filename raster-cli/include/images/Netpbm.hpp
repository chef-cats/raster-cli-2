#pragma once

#include "Image.hpp"

#include <boost/optional.hpp>

#include <fstream>

/**
 * Wrapper of type that needs to be loaded later.
 *
 * Provides method to check if the variable is loaded.
 */
template <typename Type>
using DelayLoad = boost::optional<Type>;


/**
 * Image in Netpbm format.
 *
 * Holds common data for all sub-formats of Netpbm.
 * More info: <https://en.wikipedia.org/wiki/Netpbm_format>
 */
class Netpbm : public Image {
public:
  Netpbm(const std::string& file_path);
  Netpbm(const Netpbm& rhs) = default;
  Netpbm(Netpbm&& rhs) = default;
  Netpbm& operator=(const Netpbm& rhs) = default;
  Netpbm& operator=(Netpbm&& rhs) = default;
  virtual ~Netpbm() = default;

public:
  virtual void apply(const Operation& operation) = 0;

public:
  bool is_loaded() const;

  const std::string& get_format_id() const;
  const size_t get_width() const;
  const size_t get_height() const;

protected:
  void load_check() const;

  void set_format_id(const std::string& format_id);
  void set_width(size_t width);
  void set_height(size_t height);

private:
  DelayLoad<std::string> _format_id; ///< ID of the format.
  DelayLoad<size_t> _width;          ///< Count of pixels in a row.
  DelayLoad<size_t> _height;         ///< Count of pixels in a column.
};