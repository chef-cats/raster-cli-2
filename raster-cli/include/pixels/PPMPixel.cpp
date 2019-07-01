#include <pixels/PPMPixel.hpp>
#include <utils/Constants.hpp>

PPM::Pixel::Pixel()
    : _red(PPM_PIXEL_PARTS_MIN_VALLUE), _green(PPM_PIXEL_PARTS_MIN_VALLUE),
      _blue(PPM_PIXEL_PARTS_MIN_VALLUE) {}

PPM::Pixel::Pixel(int red, int green, int blue) {
    set(red, green, blue);
}

void PPM::Pixel::set(int red, int green, int blue) {
    validate(red);
    _red = red;

    validate(green);
    _green = green;

    validate(blue);
    _blue = blue;
}

int PPM::Pixel::get_red() const {
    return _red;
}

int PPM::Pixel::get_blue() const {
    return _blue;
}

int PPM::Pixel::get_green() const {
    return _green;
}

void PPM::Pixel::validate(int value) const {
    if (value > PPM_PIXEL_PARTS_MAX_VALLUE || value < PPM_PIXEL_PARTS_MIN_VALLUE) {
        throw std::range_error("Try to set invalid value for PPM pixel");
    }
}