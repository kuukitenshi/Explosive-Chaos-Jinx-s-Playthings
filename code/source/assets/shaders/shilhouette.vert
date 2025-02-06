#version 460 core
//----------------------- shilhouette + rim light -----------------------
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

    float scale = 0.007;
    vec3 expandedPos = position + normal * scale;
    FragPos = vec3(u_model * vec4(expandedPos, 1.0));

    gl_Position = ProjectionMatrix * ViewMatrix * vec4(FragPos, 1.0);
}
