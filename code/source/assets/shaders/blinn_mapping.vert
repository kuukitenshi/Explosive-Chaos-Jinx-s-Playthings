#version 460 core
//----------------------- normal mapping + textures + blinn phong -----------------------
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 tangent;

out vec2 TexCoords;
out vec3 ViewDir;
out mat3 TBN;

uniform mat4 u_model = mat4(1.0);
uniform Camera
{
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * u_model * vec4(position, 1);
    
    TexCoords = texCoords;

    vec3 T = normalize(vec3(u_model * vec4(tangent, 0)));
    vec3 N = normalize(vec3(u_model * vec4(normal, 0)));
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);

    vec4 world_pos = u_model * vec4(position, 1);
    mat4 view_inverse = inverse(ViewMatrix); // cam pos
    ViewDir = (view_inverse[3] - world_pos).xyz;
}
