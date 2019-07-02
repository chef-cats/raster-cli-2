#pragma once
#include <images/PPM.hpp>
#include <utils/FileOperations.hpp>

#include <iostream>

/**
 * PPM pixel are color. One pixel is 24 bits: 8 for red, 8 for green, 8 for blue.
 */
class PPM::Pixel {
  public:
    Pixel();
    Pixel(int red, int green, int blue);
    Pixel(const Pixel& other) = default;
    Pixel(Pixel&& other) = default;
    Pixel& operator=(const Pixel& rhs) = default;
    Pixel& operator=(Pixel&& rhs) = default;
    ~Pixel() = default;

  public:
    void set(int red, int green, int blue);

  public:
    int get_red() const;
    int get_blue() const;
    int get_green() const;

  private:
    void validate(int value) const;

  private:
    unsigned char _red;
    unsigned char _green;
    unsigned char _blue;
};

static std::ostream& operator<<(std::ostream& out, const PPM::Pixel& pixel) {
    int red = pixel.get_red();
    out << red << " ";

    int green = pixel.get_green();
    out << green << " ";

    int blue = pixel.get_blue();
    out << blue << " ";

    return out;
}

static std::istream& operator>>(std::istream& out, PPM::Pixel& pixel) {
    int red;
    out >> red;

    int green;
    out >> green;

    int blue;
    out >> blue;

    file::operations::file_healthcheck(out, "");

    pixel.set(red, green, blue);

    return out;
}