#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 model;

out vec3 o_normal;

void main()
{
    o_normal = normalize(vertexNormal);
    gl_Position = model * vec4(vertexPosition, 1.0);
}
