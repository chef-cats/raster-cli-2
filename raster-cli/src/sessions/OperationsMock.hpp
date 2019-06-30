#pragma once

#include <operations/Operation.hpp>
#include <utils/Types.hpp>

class ToGrayscale : public Operation {};

class ToMonochrome : public Operation {};

class ToNegative : public Operation {};

class Rotate : public Operation {
  public:
    Rotate(Direction direction) {}

    Direction get_direction() const { return Direction(); }
};