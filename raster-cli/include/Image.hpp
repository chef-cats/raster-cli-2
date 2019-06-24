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
  /**
   * The constructor doesn't load the pixels from the file. It only
   * saves the file name. If you want to load the pixels, you have to 
   * invoke the load function(@see load). This lazy construction
   * will help to avoid unnecessary memory usage.
   */
  explicit Image(const std::string& file_path) : _file_path(file_path) {}
  Image(const Image& rhs) = default;
  Image(Image&& rhs) = default;
  Image& operator=(const Image& rhs) = default;
  Image& operator=(Image&& rhs) = default;
  virtual ~Image() = default;

  /**
   * This function "accepts" an Operation that will affect the image.
   *
   * @param operation [in] What operation to take effect.
   */
  virtual void apply(const Operation& operation) = 0;

private:
  std::string _file_path; ///< Path to the file that represents the image.
};