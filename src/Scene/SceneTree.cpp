#include "Scene/SceneTree.hpp"
#include <string>

SceneTree::SceneTree(SceneNode* root) : m_root(root){}

SceneTree::~SceneTree() {}

SceneTree& SceneTree::Instance(SceneNode* rootNode){
    static SceneTree* instance = new SceneTree(rootNode);
    return *instance;
}

void SceneTree::Update(bool pause) {
    if (m_root != nullptr) {
        m_root->Update(pause);
    }
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

