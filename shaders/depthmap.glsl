// ====================================================
#version 330 core

// ======================= IN =========================
in vec3 FragPos; // Import the fragment position
in vec2 v_texCoord; // Import texture coordinates from vertex shader
in vec3 myNormal; // Import normal data

// ======================= UNIFORM ====================
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientIntensity;
uniform mat4 view;

// ======================= OUT ========================
out vec4 FragColor;

void main()
{
    float near = 0.1f;
    float far = 20.0f;
    float depth = (2.0 * near * far) / (far + near - (gl_FragCoord.z * 2.0 - 1.0) * (far - near));
    float illumination = depth / far;

    FragColor = vec4(vec3(illumination), 1.0f);
}
// ==================================================================

