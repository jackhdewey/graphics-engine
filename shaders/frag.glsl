// ====================================================
#version 330 core

// ======================= IN =========================
in vec3 fragment_Pos; // Import fragment position
in vec3 fragment_Normal; // Import fragment normal
in vec2 texture_Coords; // Import texture coordinates

// ======================= UNIFORMS ====================
// Texture
uniform sampler2D u_DiffuseMap;
// Lighting
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float ambientIntensity;
uniform float specularStrength;
// Camera
uniform vec3 cameraPosition;

// ======================= OUT ========================
out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 color;

    float ambientIntensity;
    float specularStrength;

    float constant;
    float linear;
    float quadratic;
};

void main()
{
    vec3 textureColor = texture(u_DiffuseMap, texture_Coords).rgb;

    // (1) Compute ambient light
    vec3 ambient = ambientIntensity * lightColor;

    // (2) Compute lighting geometry
    vec3 normal = normalize(fragment_Normal);
    vec3 lightDir = normalize(lightPosition - fragment_Pos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(cameraPosition - fragment_Pos);

    // (2) Compute diffuse light
    float diffImpact = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffImpact * lightColor;

    // (3) Compute specular light
    float specImpact = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * specImpact * lightColor;

    // (4) Add components together to get net lighting
    vec3 lighting = diffuse + ambient + specular;

    // (5) Combine texture color and lighting
    if (gl_FrontFacing) {
        FragColor = vec4(textureColor * lighting, 1.0);
    } else {
        // Additionally color the back side the same color
        FragColor = vec4(textureColor * lighting, 1.0);
    }
}
// ==================================================================
