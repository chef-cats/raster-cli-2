#pragma once
#include <images/PGM.hpp>
#include <iostream>
#include <utils/Constants.hpp>
#include <utils/Formatter.hpp>

class PGM::Pixel {
  public:
    Pixel();
    Pixel(int value);
    Pixel(const Pixel& other) = default;
    Pixel(Pixel&& other) = default;
    Pixel& operator=(const Pixel& rhs) = default;
    Pixel& operator=(Pixel&& rhs) = default;
    ~Pixel() = default;

    bool operator==(const PGM::Pixel& rhs) { return get_value() == rhs.get_value(); }

  public:
    void set_value(int value);
    int get_value() const;
    operator size_t() const;

  private:
    unsigned char _data;
};

static std::ostream& operator<<(std::ostream& out, const PGM::Pixel& pixel) {
    int data = pixel.get_value();
    out << data;
    return out;
}

static std::istream& operator>>(std::istream& out, PGM::Pixel& pixel) {
    int data;
    out >> data;

    pixel.set_value(data);
    return out;
}
