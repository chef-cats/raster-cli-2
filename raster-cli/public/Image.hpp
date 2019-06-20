#pragma once

#include <string>

/**
 * Forward declaration of Operation.
 */
class Operation;

/**
 * Base of the image hierarchy.
 *
 * Operations on Image are handled with the visitor design pattern.
 */
class Image {
public:
  virtual ~Image() = default;

  Image(const std::string& file_path) : _file_path(file_path) {}

  /**
   * This function "accepts" an Operation that will affect the image.
   *
   * @param operation [in] What operation to take effect.
   */
  virtual void apply(const Operation& operation) = 0;

  std::string _file_path; ///< Path to the file that represents the image.
};