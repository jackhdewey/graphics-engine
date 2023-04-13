/**
 * Created by Jack Dewey on 6/21/22.
 */

#ifndef SCENETREE_HPP
#define SCENETREE_HPP

#include "SceneNode.hpp"
#include "Scene/Renderer.hpp"
#include "Scene/Shader.hpp"

/**
 * This class describes a scene tree that stores the relationships
 * between elements (objects) making up a scene
 */
class SceneTree {

public:

    /**
     * Retrieve the singleton instance of scene tree
     *
     * @param rootObj
     * @return a reference to the created scene tree
     */
    static SceneTree& Instance(SceneNode* rootNode);

    /**
     * Destructor
     */
    ~SceneTree();

    /**
     * Retrieve a pointer to the root node
     */
    SceneNode* GetRoot();

    /**
     * Randomize the locations of the root's children
     */
    void RandomizeLocations();

    /**
     * Randomize the forward directions for the root's children
     */
    void RandomizeDirections();

    /**
     * Update the entire scene tree
     *
     * @param camera
     */
    void Update(Camera*& camera, bool pause);

private:

    // Private constructor
    SceneTree(SceneNode* rootNode);

    // The root of the tree
    SceneNode* m_root;

};

#endif
