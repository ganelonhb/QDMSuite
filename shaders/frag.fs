#version 330 core

in vec3 FragPos;           // Interpolated fragment position from vertex shader
in vec3 Normal;            // Interpolated normal from vertex shader
in vec2 TexCoords;         // Interpolated texture coordinates from vertex shader

out vec4 FragColor;        // Final output color of the fragment

uniform sampler2D texture_diffuse1;   // Diffuse texture map
uniform vec3 lightPos;                // Light position
uniform vec3 viewPos;                 // Camera/view position
uniform vec3 lightColor;              // Light color

void main()
{
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (optional)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine all lighting components
    vec3 lighting = ambient + diffuse + specular;

    // Apply texture
    vec4 texColor = texture(texture_diffuse1, TexCoords);

    // Calculate final color
    FragColor = vec4(lighting, 1.0) * texColor;
}
