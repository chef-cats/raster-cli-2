#pragma once

#include "PPM.hpp"

class TextPPM : public PPM {
  public:
    TextPPM(const std::string& file_name);
    TextPPM(const TextPPM& other) = default;
    TextPPM(TextPPM&& other) = default;
    TextPPM& operator=(const TextPPM& rhs) = default;
    TextPPM& operator=(TextPPM&& rhs) = default;
    virtual ~TextPPM() = default;

  public:
    virtual void load() override;
    virtual void save() const override;

  protected:
    void read_pixels(std::ifstream& file);
    void write_pixels(std::ofstream& file) const;
};

#include <pixels/PPMPixel.hpp>