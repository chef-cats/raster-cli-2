#pragma once

#include <boost/optional.hpp>

using PGMPixel = unsigned char;

/**
 * Wrapper of type that needs to be loaded later.
 *
 * Provides method to check if the variable is loaded.
 * @todo Separate to utils file.
 */
template <typename Type>
using DelayLoad = boost::optional<Type>;