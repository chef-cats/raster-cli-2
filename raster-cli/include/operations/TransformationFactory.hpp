#pragma once

#include "Operation.hpp"
#include "OperationsMock.hpp"
#include <utils/Types.hpp>
#include <utils/Formatter.hpp>

#include <memory>

std::unique_ptr<const Operation> create_transformation(TransformationID id) {
    switch (id) {
    case TransformationID::TO_GRAYSCALE:
        return std::make_unique<ToGrayscale>();
    case TransformationID::TO_MONOCHROME:
        return std::make_unique<ToMonochrome>();
    case TransformationID::TO_NEGATIVE:
        return std::make_unique<ToNegative>();
    case TransformationID::ROTATE_LEFT:
        return std::make_unique<Rotate>(Direction::LEFT);
    case TransformationID::ROTATE_RIGHT:
        return std::make_unique<Rotate>(Direction::RIGHT);
    default:
        throw std::invalid_argument(Formatter() << "Unknown transformation ID!");
    }
}