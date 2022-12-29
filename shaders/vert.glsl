// ==================================================================
#version 330 core

// Read in attributes stored in vertex buffer object
layout(location=0)in vec3 position; 
layout(location=1)in vec2 texCoord;
layout(location=2)in vec3 normal;
layout(location=3)in vec3 tangent;
layout(location=4)in vec3 bitangent;

// Transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Fragment position in world space (for computing lighting)
out vec3 FragPos;

// Texture coordinates and vertex normals
out vec2 v_texCoord;
out vec3 v_normal;

void main()
{
    // Transform each vertex into screen space
    gl_Position = projection * view * model * vec4(position, 1.0f);

    // Transform each fragment into world space (for computing lighting)
    FragPos = vec3(model * vec4(position, 1.0f));

    // Pass normal and texture coordinates to the next stage
    v_texCoord = texCoord;
    v_normal = normal;
}
// ==================================================================
