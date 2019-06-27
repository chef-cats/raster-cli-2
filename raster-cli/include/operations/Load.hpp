#pragma once

#include "Operation.hpp"
#include <cinttypes>
#include <fstream>

class Load : public Operation {
public:
  virtual void apply_to(PGM& image) const override;

private:
  template <typename ImageType>
  void load_meta_data(ImageType& image, std::ifstream& file) const;

  void load_meta_data(PGM& image, std::ifstream& file) const;

private:
  template <typename ImageType>
  void read_from_text_file(ImageType& image, uint64_t bytes_to_read,
                           std::ifstream& file) const;

  template <typename ImageType>
  void read_from_binary_file(ImageType& image, uint64_t bytes_to_read,
                             std::ifstream& file) const;
};
