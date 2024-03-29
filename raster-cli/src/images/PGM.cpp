#include <images/PGM.hpp>
#include <operations/Operation.hpp>
#include <utils/Constants.hpp>
#include <utils/FileOperations.hpp>
#include <utils/Formatter.hpp>

namespace fop = file::operations;

PGM::PGM(const std::string& file_name) : NetpbmWithMaxValue(file_name) {}

void PGM::apply(const Operation& operation) {
    operation.apply_to(*this);
}

/**
 * throws std::logic_error - if some of the data is not loaded.
 */
void PGM::load_check() const {
    metadata_check();
    if (!_pixels) {
        throw std::logic_error(Formatter() << "The pixel of image " << get_file_path()
                                           << " are not loaded but the all metadata is.");
    }
}

/**
 * Get pixel with coordinates row and column of the image
 *
 * @throw std::out_of_range - if row values is bigger than image's height
 *                            or column values is bigger than image's width
 * @throw std::logic_error - if the image is not loaded.
 */
PGM::Pixel PGM::get_pixel(size_t row, size_t column) const {
    load_check();

    return _pixels.get()[row][column];
}

/**
 * Set new value of the pixel with coordinates row and column
 *
 * @throw std::out_of_range - if row values is bigger than image's height
 *                            or column values is bigger than image's width
 * @throw std::range_error - if the the pixel value which try to set is bigger than the
 *                           maximum possible value of the pixels for this image
 *                           (numbers of grey between black and white).
 * @throw std::logic_error - if the image is not loaded.
 */
void PGM::set_pixel(PGM::Pixel pixel, size_t row, size_t column) {
    load_check();

    size_t value = pixel;
    if (value > get_max_value()) {
        throw std::range_error(Formatter()
                               << "Try to set invalid value to " << get_file_path()
                               << ". The max value is " << get_max_value()
                               << "but you try to set " << pixel << "!");
    }
    _pixels.get()[row][column] = pixel;
}

const std::vector<std::vector<PGM::Pixel>>& PGM::get_pixels() const {
    return _pixels.get();
}

void PGM::set_pixels(const std::vector<std::vector<PGM::Pixel>>& pixels) {
    metadata_check();
    size_t max_value = get_max_value();

    if (pixels.size() != get_height()) {
        throw std::invalid_argument(Formatter() << "Try to set invalid pixel data. "
                                                << "Height of data is " << pixels.size()
                                                << ". Expected height: " << get_height());
    }

    for (auto& pixels_line : pixels) {
        if (pixels_line.size() != get_width()) {
            throw std::invalid_argument(Formatter()
                                        << "Try to set invalid pixel data. "
                                        << "Width of data is " << pixels_line.size()
                                        << ". Expected width: " << get_height());
        }

        for (auto& pixel : pixels_line) {
            if (pixel > max_value) {
                throw std::range_error(
                    Formatter() << "Try to set invalid value to " << get_file_path()
                                << ". The max value is " << max_value
                                << "but you try to set " << pixel << "!");
            }
        }
    }

    _pixels = pixels;
}
