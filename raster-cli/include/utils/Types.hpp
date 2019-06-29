#pragma once

#include <boost/optional.hpp>

using PGMPixel = unsigned char;

/**
 * Wrapper of type that needs to be loaded later.
 *
 * Provides method to check if the variable is loaded.
 */
template <typename Type>
using DelayLoad = boost::optional<Type>;

/**
 * Defines valid directions.
 *
 * Usually used when rotating images.
 */
enum class Direction : bool { LEFT, RIGHT };

/**
 * Holds valid operations IDs.
 * 
 * @todo Implement.
 */
enum class OperationID : unsigned short {};

