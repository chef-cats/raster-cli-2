#pragma once
#include <iostream>
#include <vector>
#include <pixels/PPMPixel.hpp>

template<typename T>
static std::ostream& operator<<(std::ostream& out, const std::vector<T>& pixel_list) {
    for (const auto& pixel : pixel_list) {
        out << pixel;
    }
    return out;
}

static bool operator==(const PPM::Pixel& lhs, const PPM::Pixel& rhs) {
    return lhs.get_red() == rhs.get_red() && lhs.get_green() == rhs.get_green()
           && lhs.get_blue() == rhs.get_blue();
}