// ==================================================================
#version 330 core

// ======================= IN =========================
layout(location=0)in vec3 position; 
layout(location=1)in vec2 texCoords;
layout(location=2)in vec3 normal;
layout(location=3)in vec3 tangent;
layout(location=4)in vec3 bitangent;

// ======================= UNIFORMS ====================
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// ======================= OUT ========================
out vec3 fragment_Pos;
out vec3 fragment_Normal;
out vec2 texture_Coords;

void main()
{
    vec4 fragment = model * vec4(position, 1.0f);
    gl_Position = projection * view * fragment;

    fragment_Pos = vec3(fragment);
    fragment_Normal = vec3(model * vec4(normal, 1.0f));
    texture_Coords = texCoords;
}
// ==================================================================
