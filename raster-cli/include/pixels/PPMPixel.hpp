#pragma once
#include <images/PPM.hpp>

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
    char _red;
    char _green;
    char _blue;
};