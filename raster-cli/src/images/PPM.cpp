#include <images/PPM.hpp>
#include <operations/Operation.hpp>
#include <utils/Formatter.hpp>

PPM::PPM(const std::string& file_name) : NetpbmWithMaxValue(file_name) {}

void PPM::apply(const Operation& operation) {
    operation.apply_to(*this);
}

/**
 * throws std::logic_error - if some of the data is not loaded.
 */
void PPM::load_check() const {
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
PPM::Pixel PPM::get_pixel(size_t row, size_t column) const {
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
void PPM::set_pixel(PPM::Pixel pixel, size_t row, size_t column) {
    load_check();

    validate_pixel(pixel);

    _pixels.get()[row][column] = pixel;
}

const std::vector<std::vector<PPM::Pixel>>& PPM::get_pixels() const {
    return _pixels.get();
}

void PPM::set_pixels(const std::vector<std::vector<PPM::Pixel>>& pixels) {
    metadata_check();
    size_t max_value = get_max_value();

    for (auto& pixels_line : pixels) {
        for (auto& pixel : pixels_line) {
            validate_pixel(pixel);
        }
    }

    _pixels = pixels;
}

void PPM::validate_pixel(Pixel pixel) {
    std::string error_message = Formatter() << "Try to set invalid red value to "
                                            << get_file_path() << ". The max value is "
                                            << get_max_value() << "but you try to set ";
    size_t max_value = get_max_value();

    size_t red = pixel.get_red();
    if (red > get_max_value()) {
        throw std::range_error(Formatter() << error_message << red << "!");
    }

    size_t green = pixel.get_green();
    if (green > get_max_value()) {
        throw std::range_error(Formatter() << error_message << green << "!");
    }

    size_t blue = pixel.get_blue();
    if (blue > get_max_value()) {
        throw std::range_error(Formatter() << error_message << blue << "!");
    }
}