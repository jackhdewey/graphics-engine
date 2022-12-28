// ==================================================================
#version 330 core
// Read in our attributes stored from our vertex buffer object
// We explicitly state which is the vertex information
// (The first 3 floats are positional data, we are putting in our vector)
layout(location=0)in vec3 position; 
layout(location=1)in vec2 texCoord; // Our second attribute - normals.
layout(location=2)in vec3 normal; // Our third attribute - texture coordinates.
layout(location=3)in vec3 tangent; // Our fourth attribute - tangents.
layout(location=4)in vec3 bitangent; // Our fifth attribute - bitangents.

// Transformation matrices
uniform mat4 model; // Object space
uniform mat4 view; // Object space
uniform mat4 projection; // Object space

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

    // Pass normal and texture coordinaets to the next stage in the graphics pipeline.
    v_texCoord = texCoord;
    v_normal = normal;
}
// ==================================================================
