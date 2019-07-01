#pragma once
#include <images/PGM.hpp>
#include <iostream>
#include <utils/Constants.hpp>
#include <utils/Formatter.hpp>

struct PGM::Pixel {
    unsigned char data;
    operator unsigned char() const { return data; }
};

static std::ostream& operator<<(std::ostream& out, const PGM::Pixel& pixel) {
    int data = pixel.data;
    out << data;
    return out;
}

static std::istream& operator>>(std::istream& out, PGM::Pixel& pixel) {
    int data;
    out >> data;
    if (data > PGM_PIXEL_MAX_VALLUE || data < PGM_PIXEL_MIN_VALLUE) {
        throw std::range_error(Formatter()
                               << "Try to set invalid PGM pixel value " << data);
    }
    pixel.data = data;
    return out;
}
