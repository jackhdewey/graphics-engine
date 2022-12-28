/** @file Sphere.hpp
 *  @brief Draw a simple sphere primitive.
 *
 *  Draws a simple sphere primitive, that is derived
 *  from the Object class.
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"
#include <cmath>

class Sphere : public Object {

public:

    /**
     * Constructor for the sphere
     */
    Sphere();

    /**
     * The initialization routine for this object.
     */
    void Init();
};

#endif