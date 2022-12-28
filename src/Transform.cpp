#include "Transform.hpp"

// By default, all transform matrices are also identity matrices
Transform::Transform(){
    LoadIdentity();
}

Transform::~Transform(){

}

// Resets the model transform as the identity matrix.
void Transform::LoadIdentity(){
    m_modelTransformMatrix = glm::mat4(1.0f);
}

void Transform::Translate(float x, float y, float z){
    m_modelTransformMatrix = glm::translate(m_modelTransformMatrix, glm::vec3(x,y,z));
}

void Transform::Rotate(float radians, float x, float y, float z){
    m_modelTransformMatrix = glm::rotate(m_modelTransformMatrix, radians, glm::vec3(x,y,z));
}

void Transform::Scale(float x, float y, float z){
    m_modelTransformMatrix = glm::scale(m_modelTransformMatrix, glm::vec3(x,y,z));
}

void Transform::ApplyTransform(Transform t){
    m_modelTransformMatrix = t.GetInternalMatrix();
}

// Returns a pointer to the transform matrix
GLfloat* Transform::GetTransformMatrix(){
    return &m_modelTransformMatrix[0][0];
}

// Get the raw internal matrix from the class
glm::mat4 Transform::GetInternalMatrix() const{
    return m_modelTransformMatrix;
}

// Perform a matrix multiplication with our Transform
Transform& Transform::operator*=(const Transform& t) {
    m_modelTransformMatrix =  m_modelTransformMatrix * t.GetInternalMatrix();
    return *this;
}

// Perform a matrix addition with our Transform
Transform& Transform::operator+=(const Transform& t) {
    m_modelTransformMatrix =  m_modelTransformMatrix + t.GetInternalMatrix();
    return *this;
}

// Matrix assignment
Transform& Transform::operator=(const Transform& t) {
    m_modelTransformMatrix =  t.GetInternalMatrix();
    return *this;
}

// Perform a matrix multiplication with our Transform
//       x * y should return a copy, rather than a reference
//       need to be very careful when operator overloading.
//       See operator*= for an example of returning the reference
//       and avoiding the copy.
// This code probably needs optimization (lots of new objects on the stack!)
Transform operator*(const Transform& lhs, const Transform& rhs){
    Transform result;

    result.m_modelTransformMatrix = lhs.GetInternalMatrix() * rhs.GetInternalMatrix();

    return result;
}

// Transform Addition
Transform operator+(const Transform& lhs, const Transform& rhs){
    Transform result;

    result.m_modelTransformMatrix = lhs.GetInternalMatrix() + rhs.GetInternalMatrix();

    return result;
}
