/** @file SceneNode.hpp
 *  @brief SceneNode describes an element in a 3D graphics scene graph
 *
 *  @author Jack
 *  @bug No known bugs.
 */

// TODO: Relocate shader to scene graph

#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <vector>

#include "Camera.hpp"
#include "Object.hpp"
#include "Transform.hpp"
#include "Shader.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SceneNode {
public:

    /**
     * Constructor creates a node containing the given object
     *
     * @param object the object to be stored at this node
     * @param parent the parent node for this node
     * @param wireframe
     */
    SceneNode(Object* object, SceneNode* parent, bool wireframe);

    /**
     * Constructor creates a node containing the given object
     *
     * @param object the object to be stored at this node
     * @param wireframe
     */
    SceneNode(Object* object, bool wireframe);

    /**
     * Destructor frees memory associated with this node and each of its children
     */
    ~SceneNode();

    /**
     * Retrieve the object stored at this node
     */
    Object* GetObject();

    /**
     * Return this node's parent
     */
    SceneNode* GetParent();

    /**
     * Add a child node to this node
     */
    void AddChild(SceneNode* n);

    /**
     * Add multiple child nodes to this node
     */
    void AddChildren(std::vector<Object*>* children);

    /**
     * Return the children of this node
     */
    std::vector<SceneNode*>& GetChildren();

    // Set the position for this node
    void SetPosition(float x, float y, float z);

    // Set the orientation of this node
    void SetOrientation(float theta);

    // Set the movement direction for this node.
    void SetVelocity(float x, float y, float z);

    // Get the movement direction for this node
    glm::vec3& GetVelocity();

    // Returns the local transformation transform
    Transform& GetLocalTransform();

    // Returns a SceneNode's world transform
    Transform& GetWorldTransform();

    // Updates the current SceneNode
    void Update(Camera*& camera, bool pause);

    // Draws the current SceneNode
    void Render();

    // Runs 'physics' for a bouncing balls simulation
    void BouncingBalls();

protected:

    // Parent
    SceneNode* m_parent;

private:

    // The object stored in this scene node
    Object* m_object;

    // Each SceneNode's local transform
    Transform m_localTransform;
    // We additionally can store the world transform
    Transform m_worldTransform;

    // This node's current linear velocity
    glm::vec3 m_linearVelocity;
    // This node's current angular velocity
    float m_angularVelocity;

    // Bool indicating whether we want to render in wireframe mode
    bool m_wireframe;
    // Shader for this scene
    Shader m_shader;

    // A pointer to a vector containing pointers to the children of this node
    std::vector<SceneNode*> m_children;
};

#endif
