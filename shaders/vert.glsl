// ==================================================================
#version 330 core

// ======================= IN =========================
layout(location=0)in vec3 position; 
layout(location=1)in vec2 texCoord;
layout(location=2)in vec3 normal;
layout(location=3)in vec3 tangent;
layout(location=4)in vec3 bitangent;

// ======================= UNIFORMS ====================
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// ======================= OUT ========================
out vec3 FragPos;
out vec2 v_texCoord;
out vec3 v_normal;

void main()
{
    // Transform each vertex into screen space
    gl_Position = projection * view * model * vec4(position, 1.0f);

    // Transform vertex position and normal into world space for lighting
    FragPos = vec3(model * vec4(position, 1.0f));
    v_normal = vec3(model * vec4(normal, 1.0f));

    // Pass texture coordinates to the next stage
    v_texCoord = texCoord;
}
// ==================================================================
