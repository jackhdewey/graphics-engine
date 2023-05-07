/**
 *  @file SceneNode.hpp
 *  @brief SceneNode describes an element in a scene.
 *
 *  Contains a mesh, local, and global transforms, and pointers to connected nodes.
 *
 *  @author Jack Dewey
 *  @bug No known bugs.
 */

#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include "Objects/Object.hpp"
#include "Scene/Transform.hpp"
#include "Scene/Shader.hpp"

#include "glm/vec3.hpp"

#include <vector>

class SceneNode {
private:

    // Mesh stored at this node
    Object* m_object;

    // Transform (relative to parent)
    Transform m_localTransform;
    // Transform (relative to scene - i.e. the root)
    Transform m_worldTransform;

    // Kinematic data for this node
    glm::vec3 m_linearVelocity;

    // Vector containing pointers to the children of this node
    std::vector<SceneNode*> m_children;

protected:

    // The parent of this node
    SceneNode* m_parent;

public:

    /**
     * Constructor creates a node containing the given object.
     *
     * @param object the object to be stored at this node
     * @param parent the parent node for this node
     * @param wireframe
     */
    SceneNode(Object* object, SceneNode* parent);

    /**
     * Constructor creates a node containing the given object.
     *
     * @param object the object to be stored at this node
     * @param wireframe
     */
    SceneNode(Object* object);

    /**
     * Destructor frees memory associated with this node and each of its children.
     */
    ~SceneNode();

    /**
     * Update this scene node and all its children.
     *
     * @param pause
     */
    void Update(bool pause);

    /**
     * Draws the object stored at this node.
     */
    void Render(Shader& shader);

    /**
     * Retrieve the object stored at this node.
     */
    Object* GetObject();

    /**
     * Return this node's parent.
     */
    SceneNode* GetParent();

    /**
     * Add a child node to this node.
     */
    void AddChild(SceneNode* n);

    /**
     * Add multiple child nodes to this node.
     */
    void AddChildren(std::vector<Object*>& children);

    /**
     * Return the children of this node.
     */
    std::vector<SceneNode*>& GetChildren();

    /**
     * Manually set the x,y,z position of this node.
     *
     * @param x
     * @param y
     * @param z
     */
    void SetPosition(float x, float y, float z);

    /**
     * Manually set the orientation of this node
     */
    void SetOrientation(float theta);

    /**
     * Set the movement direction for this node.
     */
    void SetVelocity(float x, float y, float z);

    /**
     * Return the velocity vector for this node.
     * @return
     */
    glm::vec3& GetVelocity();

    /**
     * Returns the local (relative to parent) transform for this node.
     * @return
     */
    Transform& GetLocalTransform();

    /**
     * Returns the world (relative to entire scene) transform for this node.
     * @return
     */
    Transform& GetWorldTransform();

    /**
     * Runs a dedicated simulation of bouncing balls in a rotating cube.
     */
    void BouncingBalls();

};

#endif
