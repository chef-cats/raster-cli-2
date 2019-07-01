#pragma once

/**
 * Forward declaration of PGM.
 */
class PGM;

/**
 * Forward declaration of PGM.
 */
class PPM;

/**
 * Base of the operation hierarchy.
 *
 * Operation is implemented as visitor of Image.
 * @warning This is a dummy implementation to keep builds happy.
 * @todo Implement it properly.
 */
class Operation {
  public:
    virtual void apply_to(PGM& image) const {}
    virtual void apply_to(PPM& image) const {}
};
