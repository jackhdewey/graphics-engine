/**
 * Created by Jack Dewey on 6/21/22.
 */

#include "SceneTree.hpp"

#include <string>
#include <iostream>

/**
 * Retrieve the singleton instance of scene tree
 *
 * @param rootObj
 * @return a reference to the created scene tree
 */
SceneTree::SceneTree(SceneNode* rootNode){
    m_root = rootNode;
}

SceneTree::~SceneTree() {

}

SceneTree& SceneTree::Instance(SceneNode* rootNode){
    static SceneTree* instance = new SceneTree(rootNode);
    return *instance;
}

SceneNode* SceneTree::GetRoot() {
    return m_root;
}

void SceneTree::RandomizeLocations() {
    std::vector<SceneNode*> children = m_root->GetChildren();
    for (int i = 0; i < children.size(); i++) {
        children.at(i)->GetLocalTransform().Translate((float) (rand() % 16 - 8),
                                                      (float) (rand() % 16 - 8),
                                                      (float) (rand() % 16 - 8));
    }
}

void SceneTree::RandomizeDirections() {
    std::vector<SceneNode*> children = m_root->GetChildren();
    for (int i = 0; i < children.size(); i++) {
        children.at(i)->SetVelocity((float(rand())/float((RAND_MAX)) * 1.0 - 0.5),
                                    (float(rand())/float((RAND_MAX)) * 1.0 - 0.5),
                                    (float(rand())/float((RAND_MAX)) * 1.0 - 0.5));

    }
}

void SceneTree::Update(Camera*& camera, bool pause) {
    m_root->Update(camera, pause);
}

void SceneTree::Render() {
    m_root->Render();
}

