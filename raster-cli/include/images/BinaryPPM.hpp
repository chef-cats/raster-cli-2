#pragma once

#include "PPM.hpp"

class BinaryPPM : public PPM {
  public:
    BinaryPPM(const std::string& file_name);
    BinaryPPM(const BinaryPPM& other) = default;
    BinaryPPM(BinaryPPM&& other) = default;
    BinaryPPM& operator=(const BinaryPPM& rhs) = default;
    BinaryPPM& operator=(BinaryPPM&& rhs) = default;
    virtual ~BinaryPPM() = default;

  public:
    virtual void load() override;
    virtual void save() const override;

  protected:
    void read_pixels(std::ifstream& file);
    void write_pixels(std::ofstream& file) const;
};