#pragma once

/**
 * Forward declaration of NetpbmImage.
 */
class NetpbmImage;

/**
 * Base of the operation hierarchy.
 *
 * Operation is implemented as visitor of Image.
 * @warning This is a dummy implementation to keep builds happy.
 * @todo Implement it properly.
 */
class Operation {
public:
  void apply_to(NetpbmImage& image) const {}
};