#pragma once
#include "NetpbmWithMaxValue.hpp"
#include "utils/Types.hpp"
#include <vector>

/**
 * Images with PGM format.
 *
 * This class represents an Portable GrayMap images.
 * These are grayscale images which have defined range of possible
 * values betwee black and white - [0, max_value]. Black is 0 and
 * max_value is white. The possible values for max_value are into the
 * [1, 255].
 */

class PGM : public NetpbmWithMaxValue {
  public:
    class Pixel;

  public:
    PGM(const std::string& file_name);
    PGM(const PGM& other) = default;
    PGM(PGM&& other) = default;
    PGM& operator=(const PGM& rhs) = default;
    PGM& operator=(PGM&& rhs) = default;
    virtual ~PGM() = default;

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
    DelayLoad<std::vector<std::vector<Pixel>>> _pixels;
};

#include <pixels/PGMPixel.hpp>