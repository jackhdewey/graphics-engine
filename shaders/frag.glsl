// ====================================================
#version 330 core

// ======================= IN =========================
in vec3 FragPos; // Import the fragment position
in vec2 v_texCoord; // Import texture coordinates from vertex shader
in vec3 myNormal; // Import normal data

// ======================= UNIFORMS ====================
uniform sampler2D u_DiffuseMap;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientIntensity;
uniform mat4 view;

// ======================= Globals ====================
float specularStrength = 0.5f;

// ======================= OUT ========================
out vec4 FragColor;

void main()
{
    vec3 textureColor = texture(u_DiffuseMap, v_texCoord).rgb;

    // (1) Compute ambient light
    vec3 ambient = ambientIntensity * lightColor;

    // (2) Compute lighting geometry
    // Note: it is always good to 'normalize' values.
    vec3 normal = normalize(myNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec3 viewPos = vec3(0.0,0.0,0.0);
    vec3 viewDir = normalize(viewPos - FragPos);

    // (2) Compute diffuse light
    float diffImpact = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffImpact * lightColor;

    // (3) Compute Specular lighting
    float specImpact = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * specImpact * lightColor;

    // Add components together to get net lighting
    vec3 lighting = diffuse + ambient + specular;

    // Combine color and lighting
    if (gl_FrontFacing) {
        FragColor = vec4(textureColor * lighting, 1.0);
    } else {
        // Additionally color the back side the same color
        FragColor = vec4(textureColor * lighting, 1.0);
    }
}
// ==================================================================
