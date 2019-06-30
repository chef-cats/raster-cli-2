#pragma once
#include "PGM.hpp"

class BinaryPGM : public PGM {
  public:
    BinaryPGM(const std::string& file_name);
    BinaryPGM(const BinaryPGM& other) = default;
    BinaryPGM(BinaryPGM&& other) = default;
    BinaryPGM& operator=(const BinaryPGM& rhs) = default;
    BinaryPGM& operator=(BinaryPGM&& rhs) = default;
    virtual ~BinaryPGM() = default;

  public:
    virtual void load() override;
    virtual void save() const override;

  protected:
    void read_pixels(std::ifstream& file);
};