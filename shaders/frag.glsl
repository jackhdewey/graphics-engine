// ====================================================
#version 330 core

// ======================= IN =========================
in vec3 FragPos; // Import the fragment position
in vec2 v_texCoord; // Import texture coordinates from vertex shader
in vec3 v_normal; // Import normal data

// ======================= UNIFORMS ====================
uniform sampler2D u_DiffuseMap;
// Camera information
uniform vec3 cameraPosition;
// Lighting information
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float ambientIntensity;
uniform float specularStrength;

// ======================= OUT ========================
out vec4 FragColor;

void main()
{
    vec3 textureColor = texture(u_DiffuseMap, v_texCoord).rgb;

    // (1) Compute ambient light
    vec3 ambient = ambientIntensity * lightColor;

    // (2) Compute lighting geometry
    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(cameraPosition - FragPos);

    // (2) Compute diffuse light
    float diffImpact = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffImpact * lightColor;

    // (3) Compute Specular lighting
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
