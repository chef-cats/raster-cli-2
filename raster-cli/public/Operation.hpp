#pragma once

class PbmImage;

class Operation {
public:
  virtual ~Operation() = default;

  virtual void apply_to(PbmImage& image) const = 0;
};