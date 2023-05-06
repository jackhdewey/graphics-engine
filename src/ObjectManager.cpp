#include "ObjectManager.hpp"

#include <string>
#include <iostream>

#include "Objects/Sphere.hpp"

// Constructor is empty
ObjectManager::ObjectManager() {
    std::cout << "(ObjectManager.cpp) Constructor called\n";
}

ObjectManager& ObjectManager::Instance() {
    static ObjectManager* instance = new ObjectManager();
    return *instance;
}

void ObjectManager::AddObject(Object*& o){
    m_objects.push_back(o);
}

// Retrieve a reference to an object
Object* ObjectManager::GetObject(unsigned int index) {
    return m_objects.at(index);
}

// Retrieve a reference to the vector of all objects
std::vector<Object*>& ObjectManager::GetObjects(){
    return m_objects;
}

void ObjectManager::GenSpheres(unsigned int num) {
    for (int i = 0; i < num; i++) {
        Object* tempObj = new Sphere();
        tempObj->LoadTexture("rock.ppm");
        m_objects.push_back(tempObj);
    }
}

void ObjectManager::Populate(SceneTree* tree) {
    std::cout << "(ObjectManager.cpp) Populating Tree\n";
    tree->GetRoot()->AddChildren(m_objects);
}