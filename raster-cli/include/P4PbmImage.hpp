#pragma once

#include "PBM.hpp"

// @todo Separate to utils file.
template <typename UnsignedType>
unsigned char high_bit_index() {
  UnsignedType bits_count = (CHAR_BIT * sizeof(UnsignedType));

  return bits_count - 1;
}

class P4PbmImage final : public PBM {
public:
  P4PbmImage(const std::string& file_path);

  std::ostream& write(std::ostream& out) const override;
  std::istream& read(std::istream& in) override;
};