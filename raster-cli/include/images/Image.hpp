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
    /**
     * Load the image from the file which was used for the image construction
     */
    virtual void load() = 0;
    /**
     * Save the image into the file with the same name as the file
     * which was used for the image construction but with a timestamp suffix
     */
    virtual void save() const = 0;

  public:
    std::string get_file_path() const { return _file_path; }

  private:
    std::string _file_path; ///< Path to the file that represents the image.
};