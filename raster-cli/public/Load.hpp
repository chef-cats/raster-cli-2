#pragma once

#include "Operation.hpp"

class PbmImage;

class Load : public Operation {
public:
  void apply_to(PbmImage& image) const override;
};