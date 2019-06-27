#pragma once

#include "Operation.hpp"
#include <images/Netpbm.hpp>
#include <cinttypes>
#include <fstream>

class Load : public Operation {
public:
  virtual void apply_to(PGM& image) const override;

private:
  void load_meta_data(Netpbm& image, std::ifstream& file) const;

  void load_meta_data(PGM& image, std::ifstream& file) const;

private:
  template <typename ImageType>
  void read_from_text_file(ImageType& image, uint64_t bytes_to_read,
                           std::ifstream& file) const;

  template <typename ImageType>
  void read_from_binary_file(ImageType& image, uint64_t bytes_to_read,
                             std::ifstream& file) const;
};

void file_healthcheck(std::ifstream& file, const std::string& file_name);
void read_line(std::ifstream& file, std::string& result);
void skip_comments(std::ifstream& file, const std::string& file_name);
