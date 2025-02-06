#version 460 core
//----------------------- cel shading -----------------------
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_model = mat4(1.0);
uniform Camera
{
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main()
{
    vec3 norm = mat3(transpose(inverse(u_model))) * normal;
    Normal = normalize(norm);

    FragPos = vec3(u_model * vec4(position, 1.0));

    gl_Position = ProjectionMatrix * ViewMatrix * vec4(FragPos, 1.0);
}
