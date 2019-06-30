#include <images/PGM.hpp>
#include <operations/Operation.hpp>
#include <utils/Constants.hpp>
#include <utils/FileOperations.hpp>
#include <utils/Formatter.hpp>

namespace fop = file::operations;

PGM::PGM(const std::string& file_name) : Netpbm(file_name) {}

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
PGMPixel PGM::get_pixel(size_t row, size_t column) const {
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
void PGM::set_pixel(PGMPixel pixel, size_t row, size_t column) {
    load_check();

    size_t value = static_cast<size_t>(pixel);
    if (value > *_max_value) {
        throw std::range_error(
            Formatter() << "Try to set invalid value to " << get_file_path()
                        << ". The max value is " << static_cast<int>(*_max_value)
                        << "but you try to set " << static_cast<int>(pixel) << "!");
    }
    _pixels.get()[row][column] = pixel;
}

size_t PGM::get_max_value() const {
    metadata_check();
    return *_max_value;
}

void PGM::metadata_check() const {
    Netpbm::metadata_check();
    if (!_max_value) {
        throw std::logic_error(
            Formatter() << "The max value is not load, but the other metadata is. File: "
                        << get_file_path());
    }
}

void PGM::load_metadata(std::ifstream& file) {
    std::string file_path = get_file_path();
    Netpbm::load_metadata(file);

    size_t max_value;
    file >> max_value;
    set_max_value(max_value);

    fop::skip_lines(file, file_path, COMMENT_SYMBOL);
    fop::file_healthcheck(file, file_path);
    fop::skip_whitespace(file);
}
/**
 * Allocate pixels after the metadata is loaded.
 * This method is invoked by Load operation.
 *
 * @throws std::logic_error - if you invoke this function
 *                            loading of the metadata.
 */
void PGM::allocate_pixels() {
    size_t row_cnt = get_height();
    size_t col_size = get_width();

    _pixels->resize(row_cnt);
    for (std::vector<PGMPixel>& row : *_pixels) {
        row.resize(col_size);
    }
}

/**
 * throw std::logic_error - when you try to change the max value for the second time
 */
void PGM::set_max_value(size_t max_value) {
    if (_max_value) {
        throw std::logic_error(Formatter() << "The max value is already set. File: "
                                           << get_file_path());
    } else {
        _max_value = max_value;
    }
}

const std::vector<std::vector<PGMPixel>>& PGM::get_pixels() const {
    return _pixels.get();
}

void PGM::set_pixels(const std::vector<std::vector<PGMPixel>>& pixels) {
    metadata_check();
    size_t max_value = get_max_value();

    for (auto& pixels_line : pixels) {
        for (auto& pixel : pixels_line) {
            if (pixel > max_value) {
                throw std::range_error(
                    Formatter()
                    << "Try to set invalid value to " << get_file_path()
                    << ". The max value is " << static_cast<int>(max_value)
                    << "but you try to set " << static_cast<int>(pixel) << "!");
            }
        }
    }

    _pixels = pixels;
}
