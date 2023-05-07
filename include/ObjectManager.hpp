/**
 *  @file ObjectManager.hpp
 *  @brief Manages allocation and storage of objects.
 *
 *  @author Jack Dewey
 *  @bug No known bugs.
 */

#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP

#include "Scene/SceneTree.hpp"
#include "Objects/Object.hpp"
#include "Objects/Sphere.hpp"

/**
 * This class manages the objects in a scene
 */
class ObjectManager{
private:

    // Constructor
    ObjectManager();

    // Objects in our scene
    std::vector<Object*> m_objects;

public:

    // Singleton
    static ObjectManager& Instance();

    // Destructor
    ~ObjectManager();

    // Add a new object
    void AddObject(Object*& o);

    // Retrieve a reference to an object
    Object* GetObject(unsigned int index);

    // Retrieve a reference to the vector of all objects
    std::vector<Object*>& GetObjects();

    // Generate a specified number of spheres
    void GenSpheres(unsigned int num);

    // Populate the scene
    void Populate(SceneTree* tree);

};

#endif
