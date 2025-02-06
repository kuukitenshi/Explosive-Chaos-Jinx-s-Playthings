#version 460 core
//----------------------- blinn phong + textures -----------------------
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 ViewDir;

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
    
    mat4 model_transpose_inverse = transpose(inverse(u_model));
    Normal = (model_transpose_inverse * vec4(normal, 0)).xyz;

    vec4 world_pos = u_model * vec4(position, 1);
    mat4 view_inverse = inverse(ViewMatrix);
    ViewDir = (view_inverse[3] - world_pos).xyz;
}
