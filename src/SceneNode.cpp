#include "SceneNode.hpp"

#include <string>
#include <iostream>

SceneNode::SceneNode(Object* object, SceneNode* parent, bool wireframe) {
    // Store the object
    m_object = object;
    m_parent = parent;
    parent->AddChild(this);
    m_angularVelocity = 0.01f;
    m_wireframe = wireframe;

    std::string vertexShader = m_shader.LoadShader("./shaders/vert.glsl");
    std::string fragmentShader = m_shader.LoadShader("./shaders/depthmap.glsl");
    m_shader.CreateProgram(vertexShader, fragmentShader);
    if (m_object->HasTexture()) {
        m_shader.SetUniform1i("u_DiffuseMap", 0);
    }
}

SceneNode::SceneNode(Object* object, bool wireframe) {

    // Store the object
    m_object = object;
    m_parent = nullptr;
    m_angularVelocity = 0.01f;
    m_wireframe = wireframe;

    std::string vertexShader = m_shader.LoadShader("./shaders/vert.glsl");
    std::string fragmentShader = m_shader.LoadShader("./shaders/depthmap.glsl");
    m_shader.CreateProgram(vertexShader, fragmentShader);
    if (m_object->HasTexture()) {
        m_shader.SetUniform1i("u_DiffuseMap", 0);
    }
}

SceneNode::~SceneNode(){
	for (unsigned int i = 0; i < m_children.size(); i++){
		delete m_children[i];
	}
}

void SceneNode::Update(Camera*& camera, bool pause){

    // Select program
    m_shader.Bind();

    // Send camera information
    m_shader.SetUniform3f("cameraPosition", camera->GetEyeXPosition(),
                                            camera->GetEyeYPosition(),
                                            camera->GetEyeZPosition());

    // Send light information
    m_shader.SetUniform3f("lightPos", 0.0f, 10.0f, 0.0f);
    m_shader.SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
    m_shader.SetUniform1f("ambientIntensity", 0.6f);
    m_shader.SetUniform1f("specularStrength", 0.5f);

    // Send the MVP Matrix
    m_shader.SetUniformMatrix4fv("model", &m_localTransform.GetInternalMatrix()[0][0]);
    m_shader.SetUniformMatrix4fv("view", &camera->GetWorldToViewMatrix()[0][0]);
    m_shader.SetUniformMatrix4fv("projection", &camera->GetProjectionMatrix()[0][0]);

    // Iterate through all the children
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->Update(camera, pause);
    }
}

void SceneNode::Render(){

    // Select program
    m_shader.Bind();

    if (m_wireframe) {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Render our object
    if (m_object != nullptr) {

        m_object->Render();

        // Also call the render routine for any 'child nodes'.
        for (int i = 0; i < m_children.size(); i++) {
            m_children[i]->Render();
        }
    }
}

void SceneNode::BouncingBalls() {

    bool pause = false;

    if (m_object != nullptr) {
        if (m_parent == nullptr) {
            m_localTransform.Rotate(m_angularVelocity, 0.0, 1.0, 0.0);
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

void SceneNode::AddChild(SceneNode* n) {
    n->m_parent = this;
    m_children.push_back(n);
}

void SceneNode::AddChildren(std::vector<Object*>* children) {
    for (int i = 0; i < children->size(); i++) {
        SceneNode* tempNode = new SceneNode(children->at(i), this, false);
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
