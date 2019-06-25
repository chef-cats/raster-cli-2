#pragma once

#include "PBM.hpp"

#include "utils/HelperFunctions.hpp"

class P4PbmImage final : public PBM {
public:
  P4PbmImage(const std::string& file_path);

  std::ostream& write(std::ostream& out) const override;
  std::istream& read(std::istream& in) override;
};