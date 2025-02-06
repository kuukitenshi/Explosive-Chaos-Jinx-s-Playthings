#version 460 core
//----------------------- normal mapping + textures + blinn phong -----------------------
in vec2 TexCoords;
in vec3 ViewDir;
in mat3 TBN;

out vec4 FragColor;

uniform sampler2D u_texture;
uniform sampler2D u_normal_texture;
uniform sampler2D u_emission_texture;
uniform sampler2D u_metalic_texture;

uniform int u_has_emissive = 0; // false

uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform float u_ka;
uniform float u_kd;
uniform float u_ks;
uniform float u_shininess;
uniform mat4 u_model = mat4(1.0);

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float emissive;
    float shininess;
};
uniform Material u_material;

uniform Camera
{
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main()
{
    // I = Me + Ma*Ia*Ka + Ip*fat[Md*kd*(N.L) + Ms*ks*(N.H)^n]
    // H = normalize(L+V)

    // Normal mapping
    vec3 norm = texture(u_normal_texture, TexCoords).rgb;
    norm = norm * 2.0 - 1.0;
    norm = normalize(TBN * norm);

    // Metallic map
    float metallic = texture(u_metalic_texture, TexCoords).r;

    vec3 light_dir = normalize(-u_light_dir);
    vec3 view_dir = normalize(ViewDir);

    vec3 half_vector = normalize(light_dir + view_dir);  // H
    float light_angle = max(dot(norm, light_dir), 0.0);  // N.L
    float view_angle = max(dot(norm, half_vector), 0.0); // N.H

    // fat = 1 / Kc + Kl * d + Kq * d^2
    float kc = 1.0;
    float kl = 0.09;
    float kq = 0.032;
    float d = length(u_light_dir);
    float fat = min(1.0 / (kc + kl * d + kq * pow(d, 2.0)), 1.0);

    // (N.H)^n
    float specular_reflection = light_angle > 0.0 ? pow(view_angle, u_material.shininess * u_shininess) : 0.0;
    // Ma*Ia*Ka
    vec3 ambient = u_ka * u_light_color * u_material.ambient;
    // Ip*fat*Md*kd*(L.N)
    vec3 diffuse = mix(u_material.diffuse, vec3(1.0), metallic) * u_kd * u_light_color * light_angle * fat;
    // Ip*fat*Ms*ks*(N.H)^n
    vec3 specular = mix(u_material.specular, u_material.specular * metallic, metallic) * u_ks * u_light_color *
                    specular_reflection * fat;
    if (u_has_emissive == 1)
    {
        // Me
        vec3 emissive = texture(u_emission_texture, TexCoords).rgb * u_material.emissive;
        FragColor = vec4(emissive + ambient + diffuse + specular, 1) * texture(u_texture, TexCoords);
    }
    else
    {
        FragColor = vec4(ambient + diffuse + specular, 1) * texture(u_texture, TexCoords);
    }
}
