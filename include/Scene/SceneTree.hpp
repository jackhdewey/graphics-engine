/**
 * Created by Jack Dewey on 6/21/22.
 */

#ifndef SCENETREE_HPP
#define SCENETREE_HPP

#include "SceneNode.hpp"

/**
 * The scene tree stores, organizes, and updates the positions of scene elements (objects).
 */
class SceneTree {

private:

    // The root of the tree
    SceneNode* m_root;

    // Private constructor
    SceneTree(SceneNode* rootNode);

public:

    /**
     * Destructor
     */
    ~SceneTree();

    /**
     * Retrieves the singleton instance of scene tree.
     *
     * @param rootObj
     * @return a reference to the created scene tree
     */
    static SceneTree& Instance(SceneNode* root);

    /**
     * Updates the scene
     *
     * @param camera
     */
    void Update(bool pause);

    /**
     * Randomizes the locations of each scene element
     */
    void RandomizeLocations();

    /**
     * Randomizes the velocities of each scene element
     */
    void RandomizeDirections();

    /**
     * Retrieves a pointer to the root node
     */
    SceneNode*& GetRoot() {
        return m_root;
    }

};

#endif
