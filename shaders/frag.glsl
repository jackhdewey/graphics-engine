// ====================================================
#version 330 core

// ======================= IN =========================
in vec3 FragPos; // Import fragment position
in vec2 FragNormal; // Import fragment normal
in vec3 TexCoords; // Import texture coordinates

// ======================= UNIFORMS ====================
// Texture
uniform sampler2D u_DiffuseMap;
// Camera
uniform vec3 cameraPosition;
// Lighting
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float ambientIntensity;
uniform float specularStrength;

struct Light {
    vec3 position;
    vec3 color;

    float ambientIntensity;
    float specularStrength;

    float constant;
    float linear;
    float quadratic;
};

// ======================= OUT ========================
out vec4 FragColor;

void main()
{
    vec3 textureColor = texture(u_DiffuseMap, TexCoords).rgb;

    // (1) Compute ambient light
    vec3 ambient = ambientIntensity * lightColor;

    // (2) Compute lighting geometry
    vec3 normal = normalize(FragNormal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(cameraPosition - FragPos);

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
