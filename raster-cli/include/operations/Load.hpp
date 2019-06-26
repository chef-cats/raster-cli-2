#pragma once

#include "Operation.hpp"

class Load : public Operation {
public:
  virtual void apply_to(PGM& image) const override;
};
