#pragma once

#include <boost/optional.hpp>

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
enum class TransformationID : unsigned short {
	TO_GRAYSCALE,
	TO_MONOCHROME,
	TO_NEGATIVE,
	ROTATE_LEFT,
	ROTATE_RIGHT
};
