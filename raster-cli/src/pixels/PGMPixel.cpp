#include <pixels/PGMPixel.hpp>

PGM::Pixel::Pixel() : _data(PGM_PIXEL_MIN_VALLUE) {}

PGM::Pixel::Pixel(int value) {
    set_value(value);
}

void PGM::Pixel::set_value(int value) {
    if (value > PGM_PIXEL_MAX_VALLUE || value < PGM_PIXEL_MIN_VALLUE) {
        throw std::range_error(Formatter()
                               << "Try to set invalid PGM pixel value " << _data);
    }
    _data = value;
}

int PGM::Pixel::get_value() const {
    return _data;
}

PGM::Pixel::operator size_t() const {
    return _data;
}
