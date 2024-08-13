#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 projection;

void main()
{
    // Apply the orthographic projection matrix to the vertex position
    gl_Position = projection * vec4(position, 1.0);
}
