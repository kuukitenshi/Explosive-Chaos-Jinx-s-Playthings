#version 460 core

layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

uniform Camera
{
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main()
{
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
    TexCoords = aPos;
}
