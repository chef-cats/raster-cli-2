#pragma once

#pragma once

#include "PGM.hpp"

class TextPGM : public PGM {
  public:
    TextPGM(const std::string& file_name);
    TextPGM(const TextPGM& other) = default;
    TextPGM(TextPGM&& other) = default;
    TextPGM& operator=(const TextPGM& rhs) = default;
    TextPGM& operator=(TextPGM&& rhs) = default;
    virtual ~TextPGM() = default;

  public:
    virtual void load() override;
    virtual void save() const override;

  protected:
    void read_pixels(std::ifstream& file);
    void write_pixels(std::ofstream& file) const;
};
