#pragma once
#include <images/NetpbmWithMaxValue.hpp>
#include <vector>


/**
 * Images with PGM format.
 *
 * This class represents a Portable PixMap images.
 * Color image.
 *
 * https://en.wikipedia.org/wiki/Netpbm_format
 */
class PPM : public NetpbmWithMaxValue {
  public:
    class Pixel;

  public:
    PPM(const std::string& file_name);
    PPM(const PPM& other) = default;
    PPM(PPM&& other) = default;
    PPM& operator=(const PPM& rhs) = default;
    PPM& operator=(PPM&& rhs) = default;
    virtual ~PPM() = default;

  public:
    virtual void apply(const Operation& operation) override;
    virtual void load() = 0;
    virtual void save() const = 0;

  public:
    virtual void load_check() const override;
    Pixel get_pixel(size_t row, size_t column) const;
    void set_pixel(Pixel pixel, size_t row, size_t column);

  protected:
    const std::vector<std::vector<Pixel>>& get_pixels() const;
    void set_pixels(const std::vector<std::vector<Pixel>>& pixels);

private: 
   void validatePixel(Pixel pixel);

  private:
    DelayLoad<std::vector<std::vector<Pixel>>> _pixels;
};

#include <pixels/PPMPixel.hpp>