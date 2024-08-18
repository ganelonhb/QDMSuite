#version 330 core

layout(location = 0) in vec3 aPosition;    // Vertex position
layout(location = 1) in vec3 aNormal;      // Vertex normal
layout(location = 2) in vec2 aTexCoords;   // Texture coordinates

out vec3 FragPos;          // Position for the fragment shader
out vec3 Normal;           // Normal for the fragment shader
out vec2 TexCoords;        // Pass the texture coordinates to the fragment shader

uniform mat4 model;        // Model matrix
uniform mat4 view;         // View matrix
uniform mat4 projection;   // Projection matrix

void main()
{
    // Calculate the vertex position in world space
    FragPos = vec3(model * vec4(aPosition, 1.0));

    // Pass the normal to the fragment shader
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Pass the texture coordinates to the fragment shader
    TexCoords = aTexCoords;

    // Calculate the final position of the vertex
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
