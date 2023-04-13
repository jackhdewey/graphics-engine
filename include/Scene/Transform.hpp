/** @file Transform.hpp
 *  @brief Responsible for holding matrix operations in model, view, and projection space
 *
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// The purpose of this class is to store transformations of 3D entities (cameras, objects, etc.)
class Transform {

public:

    // Constructor
    Transform();
    // Destructor
    ~Transform();

    // Resets to the identity matrix
    void LoadIdentity();

    // Translate along a given vector
    void Translate(float x, float y, float z);
    // Rotate around a given axis
    void Rotate(float radians, float x, float y, float z);
    // Scale each dimension by the given amount
    void Scale(float x, float y, float z);

    // Takes in a transform and sets internal matrix
    void ApplyTransform(Transform t);
    // Returns the transformation matrix
    GLfloat* GetTransformMatrix();
    // Returns the internal matrix
    glm::mat4 GetInternalMatrix() const;

    // *= operator overload (t1 is multiplied and a new result stored)
	Transform& operator*=(const Transform& t);
	// Addition operator overload
	Transform& operator+=(const Transform& t);
	// Equality operator overload
	Transform& operator=(const Transform& t);
    // Multiplication operator overload
    // Returns a new copy of the result in t3 = t1 * t2.
    friend Transform operator*(const Transform& lhs, const Transform& rhs);
    // Addition operator overload
    // Returns a new copy of the result in t3 = t1 + t2.
    friend Transform operator+(const Transform& lhs, const Transform& rhs);

private:
    // Internal representation of the transformation matrix
    glm::mat4 m_modelTransformMatrix;
};


#endif
