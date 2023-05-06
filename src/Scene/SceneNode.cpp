#include "Scene/SceneNode.hpp"
#include <string>

SceneNode::SceneNode(Object* object, SceneNode* parent) : m_object(object), m_parent(parent) {
    if (parent != nullptr) {
        parent->AddChild(this);
    }
}

SceneNode::SceneNode(Object* object) {
    m_object = object;
    m_parent = nullptr;
}

SceneNode::~SceneNode(){
	for (unsigned int i = 0; i < m_children.size(); i++){
		delete m_children[i];
	}
}

void SceneNode::Update(bool pause){

    // Empty for now

    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->Update(pause);
    }
}

void SceneNode::Render(Shader& shader){

    //if (m_wireframe) {
    //    glDisable(GL_TEXTURE_2D);
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //} else {

    //}

    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shader.SetUniformMatrix4fv("model", &m_localTransform.GetInternalMatrix()[0][0]);

    // Render our object
    if (m_object != nullptr) {
        if (m_object->HasTexture()) {
            shader.SetUniform1i("u_DiffuseMap", 0);
        }
        m_object->Render();
    }

    // Also render any 'child nodes'
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->Render(shader);
    }
}

void SceneNode::AddChild(SceneNode* n) {
    n->m_parent = this;
    m_children.push_back(n);
}

void SceneNode::AddChildren(std::vector<Object*>& children) {
    for (int i = 0; i < children.size(); i++) {
        SceneNode* tempNode = new SceneNode(children.at(i), this);
        m_children.push_back(tempNode);
    }
}

SceneNode* SceneNode::GetParent() {
    return m_parent;
}

std::vector<SceneNode*>& SceneNode::GetChildren() {
    return m_children;
}

Object* SceneNode::GetObject() {
    return m_object;
}

void SceneNode::SetPosition(float x, float y, float z) {
    m_localTransform.Translate(x, y, z);
}

void SceneNode::SetOrientation(float theta) {
    m_localTransform.Rotate(theta, 1.0, 0.0, 0.0);
}

void SceneNode::SetVelocity(float x, float y, float z) {
    m_linearVelocity = glm::vec3(x, y, z);
}

glm::vec3& SceneNode::GetVelocity() {
    return m_linearVelocity;
}

Transform& SceneNode::GetLocalTransform(){
    return m_localTransform;
}

Transform& SceneNode::GetWorldTransform(){
    return m_worldTransform;
}

// A built-in function for performing a 'bouncing ball' simulation
void SceneNode::BouncingBalls() {

    bool pause = false;

    if (m_object != nullptr) {
        if (m_parent == nullptr) {
            // m_localTransform.Rotate(m_angularVelocity, 0.0, 1.0, 0.0);
            m_worldTransform = m_localTransform;
        } else {
            m_worldTransform = m_parent->m_worldTransform * m_localTransform;

            if (!pause) {

                m_localTransform.Translate(m_linearVelocity.x, m_linearVelocity.y, m_linearVelocity.z);

                glm::vec4 position = m_localTransform.GetInternalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

                if (position.x + 1.0 > 10.0) {
                    m_localTransform.Translate(-(position.x - 9.05), 0.0, 0.0);
                    SetVelocity(-m_linearVelocity.x, m_linearVelocity.y, m_linearVelocity.z);
                }
                if (position.x - 1.0 < -10.0) {
                    m_localTransform.Translate(-(position.x + 9.05), 0.0, 0.0);
                    SetVelocity(-m_linearVelocity.x, m_linearVelocity.y, m_linearVelocity.z);
                }
                if (position.y + 1.0 > 10.0) {
                    m_localTransform.Translate(0.0, -(position.y - 9.05), 0.0);
                    SetVelocity(m_linearVelocity.x, -m_linearVelocity.y, m_linearVelocity.z);
                }
                if (position.y - 1.0 < -10.0) {
                    m_localTransform.Translate(0.0, -(position.y + 9.05), 0.0);
                    SetVelocity(m_linearVelocity.x, -m_linearVelocity.y, m_linearVelocity.z);
                }
                if (position.z + 1.0 > 10.0) {
                    m_localTransform.Translate(0.0, 0.0, -(position.z - 9.05));
                    SetVelocity(m_linearVelocity.x, m_linearVelocity.y, -m_linearVelocity.z);
                }
                if (position.z - 1.0 < -10.0) {
                    m_localTransform.Translate(0.0, 0.0, -(position.z + 9.05));
                    SetVelocity(m_linearVelocity.x, m_linearVelocity.y, -m_linearVelocity.z);
                }

                std::vector < SceneNode * > siblings = m_parent->GetChildren();

                for (int i = 1; i < siblings.size(); i++) {
                    glm::vec4 otherPosition =
                            siblings.at(i)->GetLocalTransform().GetInternalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
                    float distance = glm::sqrt((position.x - otherPosition.x) * (position.x - otherPosition.x) +
                                               (position.y - otherPosition.y) * (position.y - otherPosition.y) +
                                               (position.z - otherPosition.z) * (position.z - otherPosition.z));

                    if (distance > 1.0 && distance < 2.0) {

                        // Generate a normal for the collision and normalize
                        glm::vec4 normal = position - otherPosition;
                        glm::vec3 normal3D = glm::vec3(normal.x, normal.y, normal.z);
                        normal3D = glm::normalize(normal3D);

                        //Prevent spheres from 'locking onto' each other
                        m_localTransform.Translate(normal3D.x * 0.4, normal3D.y * 0.4, normal3D.z * 0.4);
                        siblings.at(i)->GetLocalTransform().Translate(-normal3D.x * 0.4, -normal3D.y * 0.4,
                                                                      -normal3D.z * 0.4);

                        // Reflect each of the spheres around the collision normal
                        glm::vec3 newDirection1 = glm::reflect(m_linearVelocity, normal3D);
                        glm::vec3 newDirection2 = glm::reflect(siblings.at(i)->GetVelocity(), -normal3D);
                        SetVelocity(newDirection1.x, newDirection1.y, newDirection1.z);
                        siblings.at(i)->SetVelocity(newDirection2.x, newDirection2.y, newDirection2.z);

                    }
                }
            }
        }
    }
}
